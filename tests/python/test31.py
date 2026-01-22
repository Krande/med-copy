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
# /******************************************************************************
#  * - Nom du fichier : test31.py
#  *
#  * - Description : ecriture d'une numerotation globale dans un maillage MED
#  *
#  *****************************************************************************/

import sys

from med.medfile import *
from med.medmesh import *
from med.medenum import *

MODE_ACCES=MED_ACC_RDWR

if (len(sys.argv) > 1) and (len(argv[1])>0): file=argv[1]
else: FILE="test31.med"

#/* Ouverture du fichier passe en argument */
fid = MEDfileOpen(FILE,MODE_ACCES)

sdim=MEDmeshnAxis(fid, 1)

#/* Lecture des infos concernant le premier maillage */
maa, sdim, mdim, meshtype, desc, dtunit, sort, nstep,  repere, axisname, axisunit = MEDmeshInfo(fid, 1)

print("\nMaillage de nom : |%s| , de dimension : %d , et de type %s\n"%(maa,mdim,meshtype))
print("\t -Dimension de l'espace : %d\n"%(sdim))
print("\t -Description du maillage : |%s|\n"%(desc))
print("\t -Noms des axes : |%s|\n"%(axisname))
print("\t -Unités des axes : |%s|\n"%(axisunit))
print("\t -Type de repère : %s\n"%(repere))
print("\t -Nombre d'étapes de calcul : %d\n"%(nstep))
print("\t -Unité des dates : |%s|\n"%(dtunit))


#/* Lecture du nombre de noeuds */
nnoe,chgt,trsf = MEDmeshnEntity(fid,maa,MED_NO_DT,MED_NO_IT,
                                MED_NODE,MED_NONE,MED_COORDINATE,MED_NO_CMODE)
print("Nombre de noeuds ",nnoe," \n")

if nnoe > 0 :
    numglobalnoe = MEDINT(nnoe)
for i in range(nnoe): numglobalnoe[i]=i+100

#/* ecriture de la numerotation globale */

MEDmeshGlobalNumberWr(fid,maa,MED_NO_DT,MED_NO_IT,MED_NODE,MED_NONE,nnoe,numglobalnoe)

#/* Fermeture du fichier */
MEDfileClose(fid)
