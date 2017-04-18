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

/**
 *
 * @author Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 */
public class CausalGraph {

    public final long handle;

    public CausalGraph(Solver s) {
        this.handle = initialise(s.handle);
    }

    private native long initialise(long s);

    public native void dispose();

    private void new_flaw(long f, long[] cs, String label) {
    }

    private void flaw_cost_change(long f) {
    }

    private void flaw_state_change(long f) {
    }

    private native double get_flaw_cost(long f);

    private native int get_flaw_state(long f);

    private void new_resolver(long r, long eff, String label) {
    }

    private void resolver_cost_change(long r) {
    }

    private void resolver_state_change(long r) {
    }

    private native double get_resolver_cost(long r);

    private native int get_resolver_state(long r);

    private void new_causal_link(long f, long r) {
    }
}
