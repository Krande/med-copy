/*  This file is part of MED.
 *
 *  COPYRIGHT (C) 1999 - 2025  EDF R&D, CEA/DEN
 *  MED is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  MED is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with MED.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <med.h>
#include <med_config.h>
#include <med_outils.h>

#include <string.h>

/**\ingroup MEDfile
  \brief \MEDfileCommentWrBrief
  \param fid \fid
  \param description \description
  \retval med_err \error
  \details \MEDfileCommentWrDetails
  \par This function is obsolete since 4.2.0
  \see MEDfileDescriptionWr
 */


med_err
MEDfileCommentWr(const med_idt fid,
		     const char* const description)
{
return MEDfileDescriptionWr(fid, description);
}
