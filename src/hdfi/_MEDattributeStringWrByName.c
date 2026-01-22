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
#include <hdf5.h>
#include <string.h>

med_err _MEDattributeStringWrByName(med_idt pid,
				    const char * const path,
				    const char * const attname,
				    const med_size attsize,
				    const char * const val)
{
  med_access_mode MED_ACCESS_MODE;
  med_idt         _attid=0,aid=0;
  med_err         _ret=-1;
  med_idt          type_hdf=0;
  med_bool        _attmustbecreated=MED_FALSE;
  hsize_t         _attsize=0;
  med_size        _valsize=0;
  med_idt         _datagroup1 = 0;

  if ( (MED_ACCESS_MODE = _MEDmodeAcces(pid) ) == MED_ACC_UNDEF ) {
    MED_ERR_(_ret,MED_ERR_INVALID,MED_ERR_ACCESSMODE, "MED_ACC_UNDEF" );
    SSCRUTE(attname); SSCRUTE(path);goto ERROR;
  }

  _valsize=strlen(val);
  if (_valsize > attsize) {
    MED_ERR_(_ret,MED_ERR_INVALID,MED_ERR_ATTRIBUTE, attname );
    ISCRUTE_size(_valsize);ISCRUTE_size(attsize);goto ERROR;
  }

  if ((aid = H5Screate(H5S_SCALAR)) < 0){
    MED_ERR_(_ret,MED_ERR_CREATE,MED_ERR_DATASPACE, attname );
    ISCRUTE_id(aid);
  }

  if ( (type_hdf = H5Tcopy(H5T_C_S1)) < 0) {
    MED_ERR_(_ret,MED_ERR_CREATE,MED_ERR_HDFTYPE, MED_ERR_NAME_MSG );
    SSCRUTE("H5T_C_S1"); goto ERROR;
  }

  if ( H5Tset_size(type_hdf,_valsize+1) < 0) {
    MED_ERR_(_ret,MED_ERR_CREATE,MED_ERR_HDFTYPE, MED_ERR_NAME_MSG );
    SSCRUTE("H5T_C_S1"); goto ERROR;
  }

  if ((_datagroup1 = _MEDdatagroupOuvrir(pid, path)) < 0) {
      MED_ERR_(_ret,MED_ERR_OPEN,MED_ERR_DATAGROUP,path);
      goto ERROR;
  }
  if ( (_attid=H5Aopen(_datagroup1, attname, H5P_DEFAULT ))  >= 0 )
    if ( MED_ACCESS_MODE == MED_ACC_RDEXT )  {
      MED_ERR_(_ret,MED_ERR_INVALID,MED_ERR_ACCESSMODE, "MED_ACC_RDEXT" );
      SSCRUTE(attname); goto ERROR;
    }

  /* POUR UNE RAISON NON IDENTIFIEE LES DEUX APPELS PRECEDENTS REMPLACENT L'APPEL SUIVANT	*/
  /* QUI GENERE L'ERREUR SUIVANTE EN HDF5-10.11 à l'appel de H5write				*/
  /* HDF5-DIAG: Error detected in HDF5 (1.10.11) thread 0:					*/
  /* #000: H5A.c line 613 in H5Awrite(): unable to write attribute				*/
  /*   major: Attribute										*/
  /*   minor: Write failed									*/
  /* #001: H5Aint.c line 809 in H5A__write(): unable to modify attribute			*/
  /*   major: Attribute										*/
  /*   minor: Unable to initialize object							*/
  /* #002: H5Oattribute.c line 925 in H5O__attr_write(): can't locate open attribute?		*/
  /*   major: Attribute										*/
  /*   minor: Object not found									*/

  /* if  ( (_attid=H5Aopen_by_name( pid, path, attname, H5P_DEFAULT, H5P_DEFAULT ))  >= 0 ) */
  /*   if ( MED_ACCESS_MODE == MED_ACC_RDEXT )  { */
  /*     MED_ERR_(_ret,MED_ERR_INVALID,MED_ERR_ACCESSMODE, "MED_ACC_RDEXT" ); */
  /*     SSCRUTE(attname); SSCRUTE(path);goto ERROR; */
  /*   } */

  if ( _attid > 0 ) {
    if ( (_attsize=H5Aget_storage_size(_attid) ) < 0 ) goto ERROR;
    if ( (_valsize+1) > _attsize ) {
      if (H5Aclose(_attid) < 0) {
	MED_ERR_(_ret,MED_ERR_CLOSE,MED_ERR_ATTRIBUTE,"");
	ISCRUTE_id(_attid);
	goto ERROR;
	}
      if ( H5Adelete_by_name(pid,path,attname,H5P_DEFAULT) < 0 ) goto ERROR;
      _attmustbecreated=MED_TRUE;
    }
  }

  if ( (_attid < 0) || _attmustbecreated ) {
    if ( (_attid=H5Acreate_by_name( pid, path, attname, type_hdf, aid, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT )) < 0 ) {
      MED_ERR_(_ret,MED_ERR_CREATE,MED_ERR_ATTRIBUTE, attname );
      SSCRUTE(path);goto ERROR;
    }
  }
  
  if ( H5Awrite(_attid,type_hdf,val) < 0) {
    /*H5Eprint1(stderr);*/
    MED_ERR_(_ret,MED_ERR_WRITE,MED_ERR_ATTRIBUTE, attname );
    SSCRUTE(path);goto ERROR;
  }

  _ret=0;

 ERROR:

  if (type_hdf > 0 ) if ( H5Tclose(type_hdf) < 0) {
    MED_ERR_(_ret,MED_ERR_CLOSE,MED_ERR_HDFTYPE, MED_ERR_ID_MSG );
    ISCRUTE_id(type_hdf);
  }

  if (aid > 0 ) if ( H5Sclose(aid) < 0) {
    MED_ERR_(_ret,MED_ERR_CLOSE,MED_ERR_DATASPACE, MED_ERR_ID_MSG );
    ISCRUTE_id(aid);
  }

  if (_attid >0) if ( H5Aclose(_attid) < 0) {
    MED_ERR_(_ret,MED_ERR_CLOSE,MED_ERR_ATTRIBUTE, MED_ERR_ID_MSG );
    ISCRUTE_id(_attid);
  }

  if (_datagroup1>0)     if (_MEDdatagroupFermer(_datagroup1) < 0) {
    MED_ERR_(_ret,MED_ERR_CLOSE,MED_ERR_DATAGROUP,path);
    ISCRUTE_id(_datagroup1);
  }


  return _ret;
}
