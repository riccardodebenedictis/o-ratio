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
public interface CausalGraphListener {

    public void new_flaw(long f, long[] cs, String label);

    public void flaw_state_changed(long f, LBool state);

    public void flaw_cost_changed(long f, double cost);

    public void current_flaw(long f);

    public void new_resolver(long r, long eff, String label);

    public void resolver_state_changed(long r, LBool state);

    public void current_resolver(long r);

    public void new_causal_link(long f, long r);
}
