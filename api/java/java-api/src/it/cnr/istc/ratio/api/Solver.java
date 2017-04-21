/*
 * Copyright (C) 2017 Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
package it.cnr.istc.ratio.api;

import com.google.gson.JsonArray;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import java.util.HashMap;
import java.util.Map;

/**
 *
 * @author Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 */
public class Solver {

    static {
        System.loadLibrary("libantlr4-runtime");
        System.loadLibrary("libsmt-lib");
        System.loadLibrary("libcore-lib");
        System.loadLibrary("libcg-lib");
        System.loadLibrary("libnative-api");
    }
    public final long handle;

    public Solver() {
        this.handle = initialise();
    }

    private native long initialise();

    public native void dispose();

    public State getState() {
        State state = new State();
        final Map<String, Item> items = new HashMap<>();
        JsonObject j_state = new JsonParser().parse(get_state()).getAsJsonObject();

        JsonArray items_array = j_state.get("items").getAsJsonArray();
        for (int i = 0; i < items_array.size(); i++) {
            JsonObject j_item = items_array.get(i).getAsJsonObject();
            String id = j_item.get("id").getAsString();
            String type = j_item.get("type").getAsString();
            Item item = new Item(type);
            items.put(id, item);
        }
        JsonArray atoms_array = j_state.get("atoms").getAsJsonArray();
        for (int i = 0; i < atoms_array.size(); i++) {
            JsonObject j_atom = atoms_array.get(i).getAsJsonObject();
            String id = j_atom.get("id").getAsString();
            String predicate = j_atom.get("predicate").getAsString();
            Atom atom = new Atom(predicate);
            items.put(id, atom);
            JsonArray j_atom_state = j_atom.get("state").getAsJsonArray();
            for (int j = 0; j < j_atom_state.size(); j++) {
                atom.state.add(AtomState.valueOf(j_atom_state.get(i).getAsString()));
            }
        }

        for (int i = 0; i < items_array.size(); i++) {
            JsonObject j_item = items_array.get(i).getAsJsonObject();
            Item item = items.get(j_item.get("id").getAsString());
            JsonArray j_item_refs = j_item.get("items").getAsJsonArray();
            for (int j = 0; j < j_item_refs.size(); j++) {
                JsonObject j_item_ref = j_item_refs.get(j).getAsJsonObject();
                String name = j_item_ref.get("name").getAsString();
                item.items.put(name, getItem(items, j_item_ref));
            }
        }
        for (int i = 0; i < atoms_array.size(); i++) {
            JsonObject j_atom = atoms_array.get(i).getAsJsonObject();
            Atom atom = (Atom) items.get(j_atom.get("id").getAsString());
            JsonArray j_atom_refs = j_atom.get("items").getAsJsonArray();
            for (int j = 0; j < j_atom_refs.size(); j++) {
                JsonObject j_item_ref = j_atom_refs.get(j).getAsJsonObject();
                String name = j_item_ref.get("name").getAsString();
                atom.items.put(name, getItem(items, j_item_ref));
            }
        }

        JsonArray refs_array = j_state.get("refs").getAsJsonArray();
        for (int i = 0; i < refs_array.size(); i++) {
            JsonObject j_ref = refs_array.get(i).getAsJsonObject();
            String name = j_ref.get("name").getAsString();
            state.items.put(name, getItem(items, j_ref));
        }

        return state;
    }

    private Item getItem(final Map<String, Item> items, JsonObject ref) {
        JsonObject val = ref.get("value").getAsJsonObject();
        if (val.has("lit")) {
            return new BoolItem(val.get("lit").getAsString(), LBool.valueOf(val.get("val").getAsString()));
        } else if (val.has("lin")) {
            return new ArithItem(ref.get("type").getAsString(), val.get("lin").getAsString(), val.get("val").getAsDouble(), val.has("lb") ? val.get("lb").getAsDouble() : Double.NEGATIVE_INFINITY, val.has("ub") ? val.get("ub").getAsDouble() : Double.POSITIVE_INFINITY);
        } else if (val.has("var")) {
            EnumItem ei = new EnumItem(ref.get("type").getAsString(), val.get("var").getAsString());
            JsonArray vals_array = val.get("vals").getAsJsonArray();
            for (int i = 0; i < vals_array.size(); i++) {
                ei.values.add(items.get(vals_array.get(i).getAsString()));
            }
            return ei;
        } else {
            return items.get(ref.getAsString());
        }
    }

    private native String get_state();

    public native boolean read(String script);

    public native boolean read(String... files);

    public native boolean solve();
}
