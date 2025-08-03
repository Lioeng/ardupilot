/*
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

#include "Rocket.h"
#include "AP_Vehicle/AP_Vehicle_Type.h"

const AP_HAL::HAL& hal = AP_HAL::get_HAL();

// create a global instance of the rocket object
Rocket rocket;

AP_Vehicle& AP::vehicle() { return rocket; }

void setup();
void loop();

void setup()
{
    rocket.init();
}

void loop()
{
    rocket.run();
}