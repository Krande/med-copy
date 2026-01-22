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
  \brief \MEDfileObjectDescriptionExistByPathBrief
  \param fid \fid
  \param medpath \medpath
  \param descriptionexist \descriptionexist
  \retval med_err  \error
  \details \MEDfileObjectDescriptionExistByPathDetails
  \par Remarques
  \MEDfileObjectDescriptionPathRem

*/
med_err
MEDfileObjectDescriptionExistByPath(const med_idt          fid,
				          med_path * const medpath,
			                  med_bool * const descriptionexist)
{
  med_err  _ret = -1;
  /* int      _i   = 0; */
  med_bool _descriptionexist=MED_FALSE;
  med_bool _datagroupexist   = MED_FALSE;
  med_bool _isasoftlink      = MED_FALSE;

  /*
   * On inhibe le gestionnaire d'erreur HDF
   */
  _MEDmodeErreurVerrouiller();

  *descriptionexist = MED_FALSE;

  if ( _MEDgetObjectStringPath(medpath) < 0 ) {
    MED_ERR_(_ret,MED_ERR_CALL,MED_ERR_API,"_MEDgetObjectStringPath");
    ISCRUTE(medpath->medclass);
    ISCRUTE(medpath->nname);
    /* for (_i=0;_i<medpath->nname;++_i) { */
    /*   SSCRUTE(medpath->name[_i]); */
    /* } */
    goto ERROR;
  }

  if (_MEDdatagroupExist(fid,
			 medpath->_datagroupname,
			 &_datagroupexist,
			 &_isasoftlink     ) <0 ) {
    MED_ERR_(_ret,MED_ERR_CALL,MED_ERR_API,"_MEDdatagroupExist");
    SSCRUTE(medpath->_datagroupname);
    goto ERROR;
  }

  if ( !_datagroupexist ) goto SORTIE;

  if (  _MEDattributeExist(fid,
			   medpath->_datagroupname,
			   MED_NOM_DES,
			   &_descriptionexist ) <0 ) {
    /* MED_ERR_(_ret,MED_ERR_CALL,MED_ERR_API,"_MEDattributeExist"); */
    /* SSCRUTE(medpath->_datagroupname); */
    goto SORTIE;
  }

  if ( _descriptionexist ) *descriptionexist = MED_TRUE;


 SORTIE:
  
  _ret=0;
  
 ERROR:

  return _ret;
}
