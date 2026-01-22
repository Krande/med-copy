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
#define MY_CASE(OBJ)\
  case MED_##OBJ :\
  strcpy(_datagroupname,MED_##OBJ##_GRP);\
  _objsize = MED_##OBJ##_GRP_SIZE;\
  break;

/**\ingroup MEDfile
  \brief \MEDfileObjectDescriptionRdBrief
  \param fid \fid
  \param medclass \medclass
  \param objectname \objectname
  \param description \description
  \retval med_err  \error
  \details \MEDfileObjectDescriptionRdDetails
  \par Remarques
  \MEDfileObjectDescriptionRem

*/
med_err
MEDfileObjectDescriptionRd(const med_idt           fid,
			      const med_class         medclass,
			      const char      * const objectname,
			            char      * const description)
{
  med_err  _ret = -1;
  char     _datagroupname[2*MED_NAME_SIZE+1]="";
  int      _objsize = 0;
  
  /*
   * On inhibe le gestionnaire d'erreur HDF
   */
  _MEDmodeErreurVerrouiller();

  /*
   * Give access to the class object in the local file
   */
  switch(medclass) {

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
    

    /* MY_CASE(FAMILY); Idem Suivant */
    /* MY_CASE(GROUP);  C'est un dataset, non un group hdf			               */
    /* Il serait possible d'ajouter un commentaire au datatset <groupname>	               */
    /* mais il faudrait en plus de son nom :					               */
    /*  - le nom du maillage concerné						               */
    /*  - le nom de la famille d'éléments à laquelle				               */
    /* or l'API ne prévoit qu'un nom						               */
    /* MEDmodel/MEDfile/FAS/<FAMILY_MESH_NAME_REF>/_ELEME/<FAMILY_NAME_ELEM>/_GRO/NOM  */
    /* Une première solution pourrait être une liste de noms séparés par le caractère '/' :    */
    /* objectname == <FAMILY_MESH_NAME_REF>/<FAMILY_NAME_ELEM>/NOM                             */
    /* Une deuxième solution pourrait être un objectname de type const char * const []         */
    /* mais il faudrait un paramètre supplémentaire indiquant le nombre de chaînes             */
    /* Une troisième solution pourraît être l'utlisation d'un objectId au lieu du fid avec     */
    /* une gestion du chemin relatif à l'objectId et une API permettant d'obtenir l'objectID   */
    /* en sélectionnant n'importe quel objet, mais cela necessiterait une revue complète d'API */
    /* La solution retenue est la création de l'API MEDfilePathCommentWr.c                     */
    
    /* MY_CASE(JOINT); */
    /* Besoin du nom du maillage */
    /* MEDmodel/MEDfile/JNT/<MESH_NAME_REF>/<JNTNAME> */

  default :
    MED_ERR_(_ret,MED_ERR_RANGE,MED_ERR_CLASS,_datagroupname);
   goto ERROR;
  }

  strncpy(_datagroupname+_objsize,objectname,MED_NAME_SIZE+1);
  _datagroupname[2*MED_NAME_SIZE]='\0';

  if (  _MEDattributeStringRdByName(fid,
				    _datagroupname,
				    MED_NOM_DES,
				    MED_COMMENT_SIZE,
				    description ) <0 ) {
    MED_ERR_(_ret,MED_ERR_CALL,MED_ERR_API,"_MEDattributeStringRdByName");
    SSCRUTE(_datagroupname);
    SSCRUTE(MED_NOM_DES);
    goto ERROR;
  }

  _ret=0;
  
 ERROR:

  return _ret;
}
