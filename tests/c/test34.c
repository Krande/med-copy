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

/******************************************************************************
 * - Nom du fichier : test34.c
 *
 * - Description : Tests d'existences des descriptions des objets med ayant
 *                 créés une description par l'API de création de l'objet
 *
 *****************************************************************************/

#include <med.h>
#define MESGERR 1
#include "med_utils.h"
#include <string.h>

#ifdef DEF_LECT_ECR
#define MODE_ACCES MED_ACC_RDWR
#elif DEF_LECT_AJOUT
#define MODE_ACCES MED_ACC_RDEXT
#else
#define MODE_ACCES MED_ACC_CREAT
#endif

#define _a 0.446948490915965
#define _b 0.091576213509771
#define _p1 0.11169079483905
#define _p2 0.0549758718227661

int main (int argc, char **argv)
{
  med_idt  fid = 0;
  char     meshname        [MED_NAME_SIZE+1] = "maa1";
  char     supportmeshname [MED_NAME_SIZE+1] = "supportmaa1";
  char     fieldname       [MED_NAME_SIZE+1] = "field1";
  char     jointname       [MED_NAME_SIZE+1] = "joint1";
  med_int  meshdim = 2;
  char     axisname[2*MED_SNAME_SIZE+1] = "x               y               ";
  char     axisunit[2*MED_SNAME_SIZE+1] = "cm              cm              ";
  med_bool objectexist      = MED_FALSE;
  med_bool descriptionexist = MED_FALSE;
  char     description0[MED_COMMENT_SIZE+1] = "un maillage pour test34";
  char     description1[MED_COMMENT_SIZE+1] = "++UN MAILLAGE POUR TEST34++";
  char     description2[MED_COMMENT_SIZE+1] = "";

    /* Caractéristiques du model n° 1 de localisation des points de gauss pour le champ n°1*/
  med_int   ngauss1_1 = 6;
  char      locname[MED_NAME_SIZE+1] = "Model n1";
  med_float refcoo1[12] = { -1.0,1.0, -1.0,-1.0, 1.0,-1.0, -1.0,0.0, 0.0,-1.0, 0.0,0.0 };

  /* Constantes */
  med_float gscoo1_1[12] = { 2*_b-1, 1-4*_b, 2*_b-1, 2*_b-1, 1-4*_b,
                             2*_b-1, 1-4*_a, 2*_a-1, 2*_a-1, 1-4*_a, 2*_a-1, 2*_a-1 };
  med_float wg1_1[6]     = { 4*_p2, 4*_p2, 4*_p2, 4*_p1, 4*_p1, 4*_p1 };

  char    profilename[MED_NAME_SIZE+1]  = "PROFIL(test34)";
  med_int profil1[2] = { 2, 3 };
  
  char    interpname[MED_NAME_SIZE+1] = "MED_TRIA3 interpolation family";
  const med_int nvariable=2;
  const med_int maxdegree=1;
  const med_int nmaxcoefficient=3;

  char  parametername[MED_NAME_SIZE+1]  = "parametre1";
  
  /* Creation du fichier "test34.med" */
  if ((fid = MEDfileOpen("test34.med",MED_ACC_RDWR)) < 0) {
    MESSAGE("Erreur a la creation du fichier test34.med");
    return -1;
  }

  /* Si le fichier test34.med a déjà été généré par test34 */
  if( MEDfileObjectExist(fid,MED_MESH,meshname,&objectexist) < 0) {
      MESSAGE("Erreur inattendue de test de l'existence du maillage : ");
      SSCRUTE(meshname);
  }
  if (objectexist) {
    if( MEDfileObjectDescriptionExist(fid,MED_MESH,meshname,&descriptionexist) < 0) {
      MESSAGE("Erreur inattendue de test de l'existence d'une description de maillage : ");
      SSCRUTE(meshname);
    }
    if ( descriptionexist == MED_FALSE ) {
      MESSAGE("Erreur d'absence anormale de la description du maillage : ");
      SSCRUTE(meshname);
      return -1;
    }
  }
  
  if (MEDmeshCr( fid, meshname, meshdim, meshdim, MED_UNSTRUCTURED_MESH,
		 description0,"s", MED_SORT_DTIT,
		 MED_CARTESIAN, axisname, axisunit) < 0) {
    MESSAGE("Erreur a la creation du maillage : "); SSCRUTE(meshname);
    return -1;
  }

  if( MEDfileObjectDescriptionExist(fid,MED_MESH,meshname,&descriptionexist) < 0) {
    MESSAGE("Erreur au test d'existence de la description du maillage : ");
    SSCRUTE(meshname);
    return -1;
  }
  if ( descriptionexist != MED_TRUE ) {
    MESSAGE("Erreur d'absence de la description du maillage : ");
    SSCRUTE(meshname);
    return -1;
  } else {
    if( MEDfileObjectDescriptionRd(fid,MED_MESH,meshname,description2) < 0) {
      MESSAGE("Erreur à la lecture de la description du maillage : ");
      SSCRUTE(meshname);
      return -1;
    }
    SSCRUTE(description2);
    description2[0]='\0';
  }

  if( MEDfileObjectDescriptionWr(fid,MED_MESH,meshname,description1) < 0) {
    MESSAGE("Erreur à l'écrasement de la description du maillage : ");
    SSCRUTE(meshname);
    return -1;
  }
  
  
  if ( MEDfieldCr(fid,fieldname,MED_INT,1,"comp1","unit1","dtunit1", meshname ) < 0) {
    MESSAGE("Erreur à la création du champ : ");SSCRUTE(fieldname);
    return -1;
  }
  
  strncpy(description1,"un champ pour test34",MED_COMMENT_SIZE+1);
  if( MEDfileObjectDescriptionWr(fid,MED_FIELD,fieldname,description1) < 0) {
    MESSAGE("Erreur à l'écriture de la description du champ : ");
    SSCRUTE(fieldname);
    return -1;
  }
  
  if (MEDsupportMeshCr( fid, supportmeshname, meshdim, meshdim, "un maillage support pour test34",
                        MED_CARTESIAN,axisname, axisunit) < 0) {
    MESSAGE("Erreur a la creation du maillage support : "); SSCRUTE(supportmeshname);
    return -1;
  }
  
  if( MEDfileObjectDescriptionRd(fid,MED_MESH_SUPPORT,supportmeshname,description2) < 0) {
      MESSAGE("Erreur à la lecture de la description du maillage support: ");
      SSCRUTE(supportmeshname);
      return -1;
  }
  SSCRUTE(description2);
  description2[0]='\0';
  
  if( MEDfileObjectDescriptionWr(fid,MED_MESH_SUPPORT,supportmeshname,"++un maillage support pour test34++") < 0) {
    MESSAGE("Erreur à l'écrasement de la description du maillage support : ");
    SSCRUTE(supportmeshname);
    return -1;
  }
  
  if ( MEDstructElementCr(fid,MED_PARTICLE_NAME, 3, MED_NO_MESHNAME,MED_NONE,MED_NONE) < 0) {
    MESSAGE("ERROR : creating struct element");
    return -1;
  }

  if( MEDfileObjectDescriptionWr(fid,MED_ELSTRUCT,MED_PARTICLE_NAME,"++un élément de structure pour test34++") < 0) {
    MESSAGE("Erreur à l'écritue de la description de l'élémnent de structure : ");
    SSCRUTE(MED_PARTICLE_NAME);
    return -1;
  }


  if (MEDlocalizationWr(fid, locname, MED_TRIA6, MED_TRIA6/100, refcoo1, MED_FULL_INTERLACE,
			ngauss1_1, gscoo1_1, wg1_1,
			MED_NO_INTERPOLATION, MED_NO_MESH_SUPPORT ) < 0) {
    MESSAGE("Erreur à la création du modèle de localisation n°1 : ");
    return -1;
  };

  strncpy(description1,"une localisation de points d'intégration pour test34",MED_COMMENT_SIZE+1);
  if( MEDfileObjectDescriptionWr(fid,MED_LOCALIZATION,locname,description1) < 0) {
    MESSAGE("Erreur à l'écriture de la description de localisation de points d'intégration : ");
    SSCRUTE(locname);
    return -1;
  }
  
  /* Creation d'un profil (selection  du deuxieme élément de valr1_1) */
  /* On n'utilise que la première valeur (2) du profil */
  if ( MEDprofileWr(fid,profilename,1,profil1) < 0) {
    MESSAGE("Erreur à l'écriture du profile : ");
    SSCRUTE(profilename);
    return -1;
  };
  
  strncpy(description1,"un profil de champ pour test34",MED_COMMENT_SIZE+1);
  if( MEDfileObjectDescriptionWr(fid,MED_PROFILE,profilename,description1) < 0) {
    MESSAGE("Erreur à l'écriture de la description de profile : ");
    SSCRUTE(profilename);
    return -1;
  }
  

  if (MEDinterpCr(fid, interpname, MED_TRIA3, MED_FALSE,
		  nvariable, maxdegree, nmaxcoefficient) < 0) {
    MESSAGE("ERROR : interpolation family creation ...");
    return -1;
  }

  strncpy(description1,"une interpolation de champ pour test34",MED_COMMENT_SIZE+1);
  if( MEDfileObjectDescriptionWr(fid,MED_INTERPOLATION,interpname,description1) < 0) {
    MESSAGE("Erreur à l'écriture de la description de profile : ");
    SSCRUTE(interpname);
    return -1;
  }
  
  /* Creation d'un variable scalaire flottante */
  strncpy(description1,"un parametre scalaire pour test34",MED_COMMENT_SIZE+1);
  if (MEDparameterCr(fid,parametername,MED_FLOAT64,description1,"ms") < 0) {
    MESSAGE("Erreur a la creation d'une variable scalaire flottante");
    return -1;
  }
  
  if( MEDfileObjectDescriptionExist(fid,MED_NUMERICAL_DATA,parametername,&descriptionexist) < 0) {
    MESSAGE("Erreur au test d'existence de la description du paramètre scalaire : ");
    SSCRUTE(parametername);
    return -1;
  }
  if ( descriptionexist != MED_TRUE ) {
    MESSAGE("Erreur d'absence de la description du paramètre scalaire : ");
    SSCRUTE(parametername);
    return -1;
  } else {
    if( MEDfileObjectDescriptionRd(fid,MED_NUMERICAL_DATA,parametername,description2) < 0) {
      MESSAGE("Erreur à la lecture de la description du paramètre scalaire : ");
      SSCRUTE(parametername);
      return -1;
    }
    SSCRUTE(description2);
    description2[0]='\0';
  }
  if( MEDfileObjectDescriptionWr(fid,MED_NUMERICAL_DATA,parametername,"++un paramètre scalaire pour test34++") < 0) {
    MESSAGE("Erreur à l'écritue de la description d'un paramètre scalaire : ");
    SSCRUTE(parametername);
    return -1;
  }

  /* Fermeture du fichier */
  if (MEDfileClose(fid) < 0) {
    MESSAGE("Erreur a la fermeture du fichier :");
    return -1;
  }

  return 0;
}
