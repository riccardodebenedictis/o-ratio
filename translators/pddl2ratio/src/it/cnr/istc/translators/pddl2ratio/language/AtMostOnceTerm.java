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
package it.cnr.istc.translators.pddl2ratio.language;

/**
 *
 * @author Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 */
public class AtMostOnceTerm implements Term {

    private final Term term;

    public AtMostOnceTerm(Term term) {
        this.term = term;
    }

    public Term getTerm() {
        return term;
    }

    @Override
    public Term negate() {
        throw new AssertionError("It is not possible to call negate on an at most once term..");
    }

    @Override
    public boolean updatesPredicate(Predicate predicate) {
        return false;
    }

    @Override
    public boolean updatesFunction(Function function) {
        return false;
    }

    @Override
    public String toString() {
        return "(at-most-once " + term + ')';
    }
}
