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
package it.cnr.istc.ratio.gui;

/**
 *
 * @author Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 */
public class Flaw {

    public final String label;
    public final String in_plan_var;
    double cost = Double.POSITIVE_INFINITY;
    LBool in_plan_val = LBool.Undefined;

    Flaw(String label, String in_plan_var) {
        this.label = label;
        this.in_plan_var = in_plan_var;
    }

    public double getCost() {
        return cost;
    }

    public LBool getInPlan() {
        return in_plan_val;
    }
}
