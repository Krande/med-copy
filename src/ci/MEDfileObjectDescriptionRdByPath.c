/*  This file is part of MED.
 *
 *  COPYRIGHT (C) 1999 - 2023  EDF R&D, CEA/DEN
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
  \brief \MEDfileObjectDescriptionRdByPathBrief
  \param fid \fid
  \param medpath \medpath
  \param description \description
  \retval med_err  \error
  \details \MEDfileObjectDescriptionRdByPathDetails
  \par Remarques
  \MEDfileObjectDescriptionPathRem

*/
med_err
MEDfileObjectDescriptionRdByPath(const med_idt          fid,
				       med_path * const medpath,
		                       char     * const description)
{
  med_err  _ret = -1;
  /* int      _i   = 0; */
  
  /*
   * On inhibe le gestionnaire d'erreur HDF
   */
  _MEDmodeErreurVerrouiller();

  if ( _MEDgetObjectStringPath(medpath) < 0 ) {
    MED_ERR_(_ret,MED_ERR_CALL,MED_ERR_API,"_MEDgetObjectStringPath");
    ISCRUTE(medpath->medclass);
    ISCRUTE(medpath->nname);
    /* for (_i=0;_i<medpath->nname;++_i) { */
    /*   SSCRUTE(medpath->name[_i]); */
    /* } */
    goto ERROR;
  }

  if (  _MEDattributeStringRdByName(fid,
				    medpath->_datagroupname,
				    MED_NOM_DES,
				    MED_COMMENT_SIZE,
				    description ) <0 ) {
    MED_ERR_(_ret,MED_ERR_CALL,MED_ERR_API,"_MEDattributeStringRdByName");
    SSCRUTE(medpath->_datagroupname);
    SSCRUTE(MED_NOM_DES);
    goto ERROR;
  }

 SORTIE:
  _ret=0;
  
 ERROR:

  return _ret;
}
