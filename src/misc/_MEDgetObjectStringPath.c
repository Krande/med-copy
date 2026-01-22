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

/*
Les objets de class medclass dont il est ici question sont représentés par des noms de groupes
dans le modèle HDF.
*/
#define MY_CASE(OBJ)							\
  case MED_##OBJ :							\
  strcpy(_datagroupname,MED_##OBJ##_GRP);				\
  _objsize = MED_##OBJ##_GRP_SIZE;					\
  strncpy(_datagroupname+_objsize,medpath->name[0],MED_NAME_SIZE+1);    \
  break;

#define PATH_COMPOSE(DATAGROUPNAME,OBJ,OBJECTNAME)                      \
  strcpy(DATAGROUPNAME+_pathsize,MED_##OBJ##_GRP);                      \
  _objsize  = MED_##OBJ##_GRP_SIZE;                                     \
  _namesize = strlen(OBJECTNAME);                                       \
  strncpy(DATAGROUPNAME+_pathsize+_objsize,OBJECTNAME,MED_NAME_SIZE+1); \
/* SSCRUTE(DATAGROUPNAME) */						\
  _pathsize += _objsize+_namesize;                                      \


#define MED_ERR_MEDPATH_NNAME								\
{											\
 MED_ERR_(_ret,MED_ERR_RANGE,MED_ERR_CLASS,"medpath->nname seems to be incorrect");	\
 ISCRUTE(_nname);									\
 ISCRUTE_int(medpath->medclass);							\
 goto ERROR;										\
}

med_err _MEDgetObjectStringPath(med_path * const medpath)
{
  med_err  _ret      = -1;
  size_t   _objsize  =  0;
  size_t   _namesize =  0;
  size_t   _pathsize =  0;
  med_int  _nname    = medpath->nname;
  /* char     _datagroupname[2*MED_MAX_NAME_IN_PATH*MED_NAME_SIZE+1]=""; */
  char     * const _datagroupname = medpath->_datagroupname;

  switch(medpath->medclass) {
       
  case (MED_FAMILY_ZERO):
  case (MED_FAMILY_NODE):
  case (MED_FAMILY_ELEM):
  case (MED_GROUP):
    /* /FAS/<FAMILY_MESH_NAME_REF>/_ELEME/<FAMILY_NAME_ELEM>/_GRO/NOM */
    /* medpath->name[0] : nom du maillage concerné par la famille				 */
    /* medpath->name[1] : "FAMILY_ZERO" ou nom de la famille pour MED_FAS_NOEUD, MED_FAS_ELEM    */
    /* TODO : medpath->name[2] : nom du groupe concerné						 */
    /* TODO : Il serait possible de faire évoluer la structure du group /_GRO/<GROUPNAME>/       */ 
    /* TODO : et d'attacher l'attribut DES au group /_GRO/<GROUPNAME>                            */
    /* TODO : ou plutôt créer à la racine un /GRO/<GROUPNAME> avec l'attribut DES                */
    /* TODO : car un même nom de groupe peut intervenir dans plusieurs familles                  */
    /* TODO : cela pose la question de l'intérêt d'associer un commentaire à une liste de groupe */
    /* TODO : au sein d'une famille.                                                             */
    
    if ( (_nname != 1) && (_nname !=2) /* && (_nname !=3) */ ) MED_ERR_MEDPATH_NNAME;
    
    PATH_COMPOSE(_datagroupname,FAMILY,medpath->name[0]);
    if ( medpath->medclass == MED_FAMILY_ZERO ) {
      if ( (_nname != 1) && (_nname != 2) ) MED_ERR_MEDPATH_NNAME;
      PATH_COMPOSE(_datagroupname,FAMILY_ZERO,FAMILY_ZERO);
    } else if ( (medpath->medclass == MED_FAMILY_NODE) || (medpath->medclass == MED_GROUP) ) {
      if ( (_nname !=2) /* && (_nname !=3) */ ) MED_ERR_MEDPATH_NNAME;
      PATH_COMPOSE(_datagroupname,FAMILY_NODE,medpath->name[1]);
    } else if ( (medpath->medclass == MED_FAMILY_ELEM) || (medpath->medclass == MED_GROUP) ) {
      if ( (_nname !=2) /* && (_nname !=3) */ ) MED_ERR_MEDPATH_NNAME;
      PATH_COMPOSE(_datagroupname,FAMILY_ELEM,medpath->name[1]);
    }
    if ( medpath->medclass == MED_GROUP ) {
      /* if ( (_nname !=2) ) MED_ERR_MEDPATH_NNAME; */
      strncpy(_datagroupname+_pathsize,MED_GROUP_GRP,MED_GROUP_GRP_SIZE+1);
      /* PATH_COMPOSE(_datagroupname,GROUP,MED_NOM_NOM); */
    }
    break;

  case (MED_JOINT):
    /* /JNT/<MESH_NAME_REF>/<JNTNAME> */
    if ( (_nname !=2) ) MED_ERR_MEDPATH_NNAME;
    PATH_COMPOSE(_datagroupname,JOINT,medpath->name[0]);
    strncpy(_datagroupname+_pathsize,"/",2);
    strncpy(_datagroupname+_pathsize+1,medpath->name[1],MED_NAME_SIZE+1);
    break;

    if ( (_nname !=1) ) MED_ERR_MEDPATH_NNAME;
    MY_CASE(MESH);
    MY_CASE(FIELD);
    MY_CASE(MESH_SUPPORT);
    MY_CASE(ELSTRUCT);
    MY_CASE(EQUIVALENCE);
    MY_CASE(LOCALIZATION);
    MY_CASE(PROFILE);
    MY_CASE(INTERPOLATION);
    MY_CASE(NUMERICAL_DATA);
    MY_CASE(FILE);

   default :
     MED_ERR_(_ret,MED_ERR_RANGE,MED_ERR_CLASS,medpath->medclass);
     goto ERROR;
   }
  
  _datagroupname[MED_MAX_DATAGROUPNAME_IN_PATH+1]='\0';
  /* SSCRUTE(_datagroupname); */

  _ret=0;
  
 ERROR:
  return _ret;
}   

