/* This file is part of Plaine.
 *
 * Plaine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Plaine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Plaine. If not, see <http://www.gnu.org/licenses/>.
 */

#include "util/NaN.h"

void notNanAssert(const btQuaternion &quat)
{
    notNanAssert(quat.getX());
    notNanAssert(quat.getY());
    notNanAssert(quat.getZ());
    notNanAssert(quat.getW());
}

void notNanAssert(const btVector3 &vec)
{
    notNanAssert(vec.getX());
    notNanAssert(vec.getY());
    notNanAssert(vec.getZ());
}

void notNanAssert(const btTransform &transform)
{
    notNanAssert(transform.getOrigin());
    notNanAssert(transform.getRotation());
}
