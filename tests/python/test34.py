#! /usr/bin/env python
# -*- coding:utf-8 -*-
# /*  This file is part of MED.
#  *
#  *  COPYRIGHT (C) 1999 - 2023  EDF R&D, CEA/DEN
#  *  MED is free software: you can redistribute it and/or modify
#  *  it under the terms of the GNU Lesser General Public License as published by
#  *  the Free Software Foundation, either version 3 of the License, or
#  *  (at your option) any later version.
#  *
#  *  MED is distributed in the hope that it will be useful,
#  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  *  GNU Lesser General Public License for more details.
#  *
#  *  You should have received a copy of the GNU Lesser General Public License
#  *  along with MED.  If not, see <http://www.gnu.org/licenses/>.
#  */
#
# / ******************************************************************************
#  * - Nom du fichier : test34.c
#  *
#  * - Description : Tests d'existences des descriptions des objets med ayant
#  *                 créés une description par l'API de création de l'objet
#  *
#  ****************************************************************************/
#
#from __future__ import division

from med.medfile import *
from med.medmesh import *
from med.medfield import *
from med.medenum import *
from med.medprofile import *
from med.medlocalization import *
from med.medlink import *
from med.medsubdomain import *
from med.medstructelement import *
from med.medinterp import *
from med.medparameter import *


_a=0.446948490915965
_b=0.091576213509771
_p1=0.11169079483905
_p2=0.0549758718227661

filename="test34.med"

fid = 0
meshname        = "maa1"
supportmeshname = "supportmaa1"
fieldname       = "field1"
jointname       = "joint1"
meshdim         = 2
axisname        = "x               y               "
axisunit        = "cm              cm              "
objectexist      = MED_FALSE
descriptionexist = MED_FALSE

description0 = "un maillage pour test34"
description1 = "++UN MAILLAGE POUR TEST34++"
description2 = ""

locname   = "Model n1"
ngauss1_1 = 6
refcoo1=MEDFLOAT([ -1.0,1.0, -1.0,-1.0, 1.0,-1.0, -1.0,0.0, 0.0,-1.0, 0.0,0.0 ])

# /* Constantes */
gscoo1_1= MEDFLOAT([ 2*_b-1, 1-4*_b, 2*_b-1, 2*_b-1, 1-4*_b,
                     2*_b-1, 1-4*_a, 2*_a-1, 2*_a-1, 1-4*_a, 2*_a-1, 2*_a-1 ])
wg1_1   = MEDFLOAT([ 4*_p2, 4*_p2, 4*_p2, 4*_p1, 4*_p1, 4*_p1 ])


profilename = "PROFIL(test34)"
profil1     = MEDINT([ 2, 3 ])

interpname      = "MED_TRIA3 interpolation family"
nvariable       = 2
maxdegree       = 1
nmaxcoefficient = 3

parametername   = "parametre1"

# /* ouverture du fichier */
fid=MEDfileOpen(filename,MED_ACC_RDWR)

# /* Si le fichier test34.med a déjà été généré par test34 */
if MEDfileObjectExist(fid,MED_MESH,meshname):
    descriptionexist=MEDfileObjectDescriptionExist(fid,MED_MESH,meshname)
    if descriptionexist == MED_FALSE :
        raise Exception("Ereur d'absence anormale de la description du maillage : "+meshname)


MEDmeshCr( fid, meshname, meshdim, meshdim, MED_UNSTRUCTURED_MESH,
	   description0,"s", MED_SORT_DTIT,
	   MED_CARTESIAN, axisname, axisunit)

descriptionexist=MEDfileObjectDescriptionExist(fid,MED_MESH,meshname)
if descriptionexist != MED_TRUE :
    raise Exception("Ereur d'absence anormale de la description du maillage : "+meshname)
else :
    description2=MEDfileObjectDescriptionRd(fid,MED_MESH,meshname)
    print(description2)

MEDfileObjectDescriptionWr(fid,MED_MESH,meshname,description1)


MEDfieldCr(fid,fieldname,MED_INT,1,"comp1","unit1","dtunit1", meshname)

description1="un champ pour test34".zfill(MED_COMMENT_SIZE)
MEDfileObjectDescriptionWr(fid,MED_FIELD,fieldname,description1)

MEDsupportMeshCr(fid, supportmeshname, meshdim, meshdim, "un maillage support pour test34",
                        MED_CARTESIAN,axisname, axisunit)
descriptionexist=MEDfileObjectDescriptionExist(fid,MED_MESH_SUPPORT,supportmeshname)
if descriptionexist != MED_TRUE :
    raise Exception("Ereur d'absence anormale de la description du maillage support : "
                    +supportmeshname)
else :
    description2=MEDfileObjectDescriptionRd(fid,MED_MESH_SUPPORT,supportmeshname)
    print(description2)
MEDfileObjectDescriptionWr(fid,MED_MESH_SUPPORT,supportmeshname,
                           "++un maillage support pour test34++")



MEDstructElementCr(fid,MED_PARTICLE_NAME, 3, MED_NO_MESHNAME,MED_NONE,MED_NONE)
MEDfileObjectDescriptionWr(fid,MED_ELSTRUCT,MED_PARTICLE_NAME,
                           "++un élément de structure pour test34++")


MEDlocalizationWr(fid, locname, MED_TRIA6, MED_TRIA6//100, refcoo1, MED_FULL_INTERLACE,
			ngauss1_1, gscoo1_1, wg1_1,
			MED_NO_INTERPOLATION, MED_NO_MESH_SUPPORT )
description1="une localisation de points d'intégration pour test34"
MEDfileObjectDescriptionWr(fid,MED_LOCALIZATION,locname,description1)


MEDprofileWr(fid,profilename,1,profil1)
description1="un profil de champ pour test34"
MEDfileObjectDescriptionWr(fid,MED_PROFILE,profilename,description1)


MEDinterpCr(fid, interpname, MED_TRIA3, MED_FALSE,
		  nvariable, maxdegree, nmaxcoefficient)
description1="une interpolation de champ pour test34"
MEDfileObjectDescriptionWr(fid,MED_INTERPOLATION,interpname,description1)


#/* Creation d'un variable scalaire flottante */
description1="un parametre scalaire pour test34"
MEDparameterCr(fid,parametername,MED_FLOAT64,description1,"ms")
descriptionexist=MEDfileObjectDescriptionExist(fid,MED_NUMERICAL_DATA,parametername)
if descriptionexist != MED_TRUE :
    raise Exception("Ereur d'absence anormale de la description du parametre scalaire : "
                    +parametername)
else :
    description2=MEDfileObjectDescriptionRd(fid,MED_NUMERICAL_DATA,parametername)
    print(description2)
MEDfileObjectDescriptionWr(fid,MED_NUMERICAL_DATA,parametername,
                           "++un parametre scalaire pour test34++")

MEDfileClose(fid)
