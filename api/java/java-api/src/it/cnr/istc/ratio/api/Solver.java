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
public class Solver {

    static {
        System.loadLibrary("libantlr4-runtime");
        System.loadLibrary("libsmt-lib");
        System.loadLibrary("libcore-lib");
        System.loadLibrary("libcg-lib");
        System.loadLibrary("libnative-api");
    }
    private long handle;

    public Solver() {
        initialise();
    }

    public native boolean read(String script);

    public native boolean read(String... files);

    public native boolean solve();

    private native void initialise();

    public native void dispose();
}
