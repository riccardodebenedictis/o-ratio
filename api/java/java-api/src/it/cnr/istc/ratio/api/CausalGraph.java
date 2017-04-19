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

import java.util.ArrayList;
import java.util.Collection;

/**
 *
 * @author Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 */
public class CausalGraph {

    public final long handle;
    private final Collection<CausalGraphListener> listeners = new ArrayList<>();

    public CausalGraph(Solver s) {
        this.handle = initialise(s.handle);
    }

    private native long initialise(long s);

    public native void dispose();

    private void new_flaw(long f, long[] cs, String label) {
        listeners.parallelStream().forEach(l -> l.new_flaw(f, cs, label));
    }

    private void flaw_state_changed(long f, int state) {
        listeners.parallelStream().forEach(l -> l.flaw_state_changed(f, LBool.values()[state]));
    }

    private void flaw_cost_changed(long f, double cost) {
        listeners.parallelStream().forEach(l -> l.flaw_cost_changed(f, cost));
    }

    private void current_flaw(long f) {
        listeners.parallelStream().forEach(l -> l.current_flaw(f));
    }

    private void new_resolver(long r, long eff, String label) {
        listeners.parallelStream().forEach(l -> l.new_resolver(r, eff, label));
    }

    private void resolver_state_changed(long r, int state) {
        listeners.parallelStream().forEach(l -> l.resolver_state_changed(r, LBool.values()[state]));
    }

    private void current_resolver(long r) {
        listeners.parallelStream().forEach(l -> l.current_resolver(r));
    }

    private void new_causal_link(long f, long r) {
        listeners.parallelStream().forEach(l -> l.new_causal_link(f, r));
    }

    public void addCausalGraphListener(CausalGraphListener listener) {
        listeners.add(listener);
    }

    public void removeCausalGraphListener(CausalGraphListener listener) {
        listeners.remove(listener);
    }
}
