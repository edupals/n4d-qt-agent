/*
   N4D Qt agent

    Copyright (C) 2024  Enrique Medina Gremaldos <quique@necos.es>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef N4D_AGENT_LOCALE
#define N4D_AGENT_LOCALE

#include <libintl.h>
#include <locale.h>
#include <QString>

namespace edupals
{
    namespace locale
    {
        static void domain(const char* d)
        {
            textdomain(d);
        }
        
        static QString T(const char* s)
        {
            return QString::fromUtf8(gettext(s));
        }
    }
}

#endif
