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

/* 
 * File:   type_declaration_listener.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 13, 2017, 12:29 PM
 */

#ifndef TYPE_DECLARATION_LISTENER_H
#define TYPE_DECLARATION_LISTENER_H

#include "parser/ratioBaseListener.h"

namespace ratio {

    class core;
    class scope;

    class type_declaration_listener : public ratioBaseListener {
    public:
        type_declaration_listener(core& c);
        type_declaration_listener(const type_declaration_listener& orig) = delete;
        virtual ~type_declaration_listener();

    private:
        void enterCompilation_unit(ratioParser::Compilation_unitContext* ctx) override;
        void enterTypedef_declaration(ratioParser::Typedef_declarationContext* ctx) override;
        void enterEnum_declaration(ratioParser::Enum_declarationContext* ctx) override;
        void enterClass_declaration(ratioParser::Class_declarationContext* ctx) override;
        void exitClass_declaration(ratioParser::Class_declarationContext* ctx) override;
        void enterClass_type(ratioParser::Class_typeContext* ctx) override;

    private:
        core& _core;
        scope* _scope;
    };
}

#endif /* TYPE_DECLARATION_LISTENER_H */

