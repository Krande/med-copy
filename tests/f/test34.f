C*  This file is part of MED.
C*
C*  COPYRIGHT (C) 1999 - 2023  EDF R&D, CEA/DEN
C*  MED is free software: you can redistribute it and/or modify
C*  it under the terms of the GNU Lesser General Public License as published by
C*  the Free Software Foundation, either version 3 of the License, or
C*  (at your option) any later version.
C*
C*  MED is distributed in the hope that it will be useful,
C*  but WITHOUT ANY WARRANTY; without even the implied warranty of
C*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
C*  GNU Lesser General Public License for more details.
C*
C*  You should have received a copy of the GNU Lesser General Public License
C*  along with MED.  If not, see <http://www.gnu.org/licenses/>.
C*

C ******************************************************************************
C * - Nom du fichier : test34.f
C *
C * - Description : Tests d'existences des descriptions des objets med ayant
C *                 créés une description par l'API de création de l'objet
C *
C ******************************************************************************
        program test34
C     
        implicit none
        include 'med.hf'
C
        integer*8    fid
        integer      ret,USER_INTERLACE,USER_MODE
        integer      FTYPECHA
        real*8       a,b,p1,p2,dt

        character*64 maa1,maa2,maa3
        character*13 lien_maa2
        character*16 nomcoo(3)
        character*16 unicoo(3)
C       CHAMP N°1
        character*64 nomcha1
        character*16 comp1(2), unit1(2)
        character*16 dtunit1, nounit
        integer      ncomp1
C       MODEL N°1 DE LOC. DES PTS DE GAUSS PR CHAMP1
        integer      ngauss1_1
        character*64 gauss1_1
        real*8       refcoo1(12), gscoo1_1(12), wg1_1(6)
        integer      nval1_1, nent1_1
        real*8       valr1_1(1*6*2)
C       MODEL N°2 DE LOC. DES PTS DE GAUSS PR CHAMP1
        integer      ngauss1_2
        character*64 gauss1_2
        real*8       gscoo1_2(6), wg1_2(3)
        integer      nval1_2, nent1_2
        real*8       valr1_2(2*3*2)
        real*8       valr1_2p(2*3)
C       MODEL N°3 DE LOC. DES PTS DE GAUSS PR CHAMP1
        integer      ngauss1_3,nval1_3, nent1_3
        real*8       valr1_3(2*3*2)
        real*8       valr1_3p(2*2)

C       CHAMP N°2
        character*64 nomcha2
        character*16 comp2(3), unit2(3)
        integer      ncomp2, nval2
        integer      valr2(5*3),   valr2p(3*3)

C       CHAMP N°3
        character*64 nomcha3
        character*16 comp3(2), unit3(2)
        integer      ncomp3, nval3, nent3
        integer      valr3(5*4*2),   valr3p(3*4*2)

C       PROFILS UTILISES
        character*64 nomprofil1
        integer      profil1(2) , profil2(3)

C       DESCRIPTIONS UTILISES
        character*200 des0,des1,des2

        integer oexist, dexist

C       MAILLAGE SUPPORT
        character*64 smname1
        integer sdim1,mdim1
        parameter (sdim1=2, mdim1=2)
        parameter (smname1 = "supportMesh1")
        
C       ELEMENT DE STRUCTURE
        integer mtype1
        
        parameter ( a=0.446948490915965D0, b=0.091576213509771D0    )
        parameter ( p1=0.11169079483905D0, p2=0.0549758718227661D0  )
C       MAILLAGES
        parameter ( maa1 = "maa1", maa2 = "maa2", maa3 = "maa3" )
        parameter ( lien_maa2= "./testfoo.med"                  )
C       CHAMP N°1
        parameter ( nomcha1 = "champ reel" )
        parameter ( ncomp1 = 2 )
        parameter ( dtunit1 = "                ")
        parameter ( nounit  = "                ")
C       MODEL N°1 DE LOC. DES PTS DE GAUSS PR CHAMP1
        parameter ( gauss1_1 = "Model n1" )
        parameter ( ngauss1_1 = 6 )
C       MODEL N°2 DE LOC. DES PTS DE GAUSS PR CHAMP1
        parameter ( gauss1_2  = "Model n2" )
        parameter ( ngauss1_2 = 3 )
C       MODEL N°3 DE LOC. DES PTS DE GAUSS PR CHAMP1
        parameter ( ngauss1_3 = 6 )
        parameter ( nval1_3 = 6 )
C       CHAMP N°2
        parameter ( nomcha2="champ entier")
        parameter ( ncomp2 = 3, nval2= 5  )
C       CHAMP N°3
        parameter ( nomcha3="champ entier 3")
        parameter ( ncomp3 = 2, nval3= 5*4  )
C       PROFILS
        parameter ( nomprofil1  = "PROFIL(champ(1))" )
        
C       CHAMP N°1
        data comp1 /"comp1", "comp2"/
        data unit1 /"unit1","unit2"/
C       MODEL N°1 DE LOC. DES PTS DE GAUSS PR CHAMP1
        data nval1_1  / 1*6 /
        data nent1_1  / 1 /
        data refcoo1  / -1.0,1.0, -1.0,-1.0, 1.0,-1.0, -1.0,0.0, 
     1                  0.0,-1.0, 0.0,0.0 / 
        data valr1_1  /  0.0,1.0, 2.0,3.0, 10.0,11.0, 12.0,13.0,
     1                   20.0,21.0, 22.0,23.0/
C       MODEL N°2 DE LOC. DES PTS DE GAUSS PR CHAMP1
        data nent1_2  / 2 /
        data valr1_2  / 0.0,1.0, 2.0,3.0, 10.0,11.0,
     1                  12.0,13.0, 20.0,21.0, 22.0,23.0 /
        data valr1_2p / 12.0,13.0, 20.0,21.0, 22.0,23.0 /
C       MODEL N°3 DE LOC. DES PTS DE GAUSS PR CHAMP1
        data nent1_3  / 6 /
        data valr1_3  / 0.0,1.0, 2.0,3.0, 10.0,11.0, 12.0,13.0, 
     1                  20.0,21.0, 22.0,23.0 /
        data valr1_3p / 2.0,3.0, 10.0,11.0   /
C       CHAMP N°2
        data comp2 /"comp1", "comp2", "comp3"/
        data unit2 /"unit1","unit2", "unit3"/
        data valr2 / 0,1,2, 10,11,12, 20,21,22, 30,31,32, 40,41,42 /
        data valr2p / 0,1,2,           20,21,22,           40,41,42 /
C       CHAMP N°3
        data nent3 / 5 /
        data comp3 /"comp1", "comp2"/
        data unit3 /"unit1","unit2"/
        data valr3 / 0,1, 10,11, 20,21, 30,31,
     1           40,41, 50,51, 60,61, 70,71,
     1           80,81, 90,91, 100,101, 110,111,
     1           120,121, 130,131, 140,141, 150,151,
     1           160,161, 170,171, 180,181, 190,191 /
        data valr3p / 0,1, 10,11, 20,21, 30,31,
     1            80,81, 90,91, 100,101, 110,111,
     1            160,161, 170,171, 180,181, 190,191 /


C       PROFILS
        data profil1 /2,3/
        data profil2 /1,3,5/

        data  nomcoo /"x","y","z"/, unicoo /"cm","cm","cm"/
        
        ret = 0

        gscoo1_1(1) =  2*b-1
        gscoo1_1(2) =  1-4*b
        gscoo1_1(3) =  2*b-1
        gscoo1_1(4) =  2*b-1
        gscoo1_1(5) =  1-4*b
        gscoo1_1(6) =  2*b-1
        gscoo1_1(7) =  1-4*a
        gscoo1_1(8) =  2*a-1
        gscoo1_1(9) =  2*a-1
        gscoo1_1(10) =  1-4*a
        gscoo1_1(11) =  2*a-1
        gscoo1_1(12) =  2*a-1

        wg1_1(1) =  4*p2
        wg1_1(2) =  4*p2
        wg1_1(3) =  4*p2
        wg1_1(4) =  4*p1
        wg1_1(5) =  4*p1
        wg1_1(6) =  4*p1

        nval1_2 = 2*3
        gscoo1_2(1) = -2.0D0/3
        gscoo1_2(2) =  1.0D0/3 
        gscoo1_2(3) = -2.0D0/3
        gscoo1_2(4) = -2.0D0/3
        gscoo1_2(5) =  1.0D0/3
        gscoo1_2(6) = -2.0D0/3

        wg1_2(1) =  2.0D0/3
        wg1_2(2) =  2.0D0/3
        wg1_2(3) =  2.0D0/3 

        des0 = "un maillage pour test34"
        des1 = "++UN MAILLAGE POUR TEST34++"
        des2 = ""

C     ** ouverture du fichier                            **
        call mfiope(fid,'test34.med', MED_ACC_RDWR, ret)
        print *,ret
        if (ret .ne. 0 ) then
           print *,'Erreur à l''ouverture du fichier  : ','test34.med'
           call efexit(-1)
        endif


C     ** Si le fichier test34.med a déjà été généré par test34 **
        call mfioex(fid, MED_MESH, maa1, oexist, ret)
        print *,ret
        if (ret .ne. 0 ) then
           print *,'Erreur inattendue de test d''existence du maillage'
        endif
        print *,"Maillage maa1 existe : ",oexist
        if (oexist .eq. MED_TRUE) then
           call mfiodx(fid, MED_MESH, maa1, dexist, ret)
           if (ret .ne. 0 ) then
              print *,'Erreur inattendue de test d''existence d''une',
     &        ' description  maillage'
           endif
           if (dexist .eq. MED_FALSE) then
              print *,'Erreur d''absence anormale de la description',
     &        ' du maillage : ',maa1
           endif
        endif
        
C     ** creation du maillage maa1 de dimension 3         **
        call mmhcre(fid,maa1,3,3,
     &     MED_UNSTRUCTURED_MESH,des0, 
     &     "",MED_SORT_DTIT,MED_CARTESIAN,nomcoo,unicoo,ret)
        print *,ret
        if (ret .ne. 0 ) then
           print *,'Erreur à la création du maillage : ', maa1
           call efexit(-1)
        endif

        call mfiodx(fid, MED_MESH, maa1, dexist, ret)
        if (ret .ne. 0 ) then
           print *,'Erreur inattendue de test d''existence d''une',
     &          ' description  maillage'
        endif
        if (dexist .ne. MED_TRUE) then
           print *,'Erreur d''absence anormale de la description',
     &          ' du maillage : ',maa1
        else
           call mfiodr(fid, MED_MESH, maa1, des2, ret)
           print *,'description2 : ',des2
        endif

        call mfiodw(fid, MED_MESH, maa1, des1, ret)
        if (ret .ne. 0 ) then
           print *,'Erreur inattendue d''écriture de la',
     &          ' description du maillage'
        endif

        
C     ** creation du champ réel n°1                        **
        call mfdcre(fid,nomcha1,MED_INT,ncomp1,comp1,unit1,
     &              dtunit1,maa1,ret)
        print *,ret
        if (ret .ne. 0 ) then
           print *,'Erreur à la création du champ : ', nomcha1
        endif
        des1="un champ pour test34"
        call mfiodw(fid, MED_FIELD, nomcha1, des1, ret)
        if (ret .ne. 0 ) then
           print *,'Erreur inattendue d''écriture de la',
     &          ' description de champ',nomcha1
        endif
      
C     ** support mesh creation : 2D
        call msmcre(fid,smname1,sdim1,mdim1,
     &   'un maillage support pour test34',
     &            MED_CARTESIAN, nomcoo, unicoo, ret)
        print *,'Support mesh creation : 2D space dimension',ret
        if (ret .ne. 0 ) then
           print *,'ERROR : support mesh creation'
        endif

        call mfiodx(fid, MED_MESH_SUPPORT, smname1, dexist, ret)
        if (ret .ne. 0 ) then
           print *,'Erreur inattendue de test d''existence d''une',
     &          ' description de maillage support'
        endif
        if (dexist .ne. MED_TRUE) then
           print *,'Erreur d''absence anormale de la description',
     &          ' du maillage support: ',smname1
        else
           call mfiodr(fid, MED_MESH_SUPPORT, smname1, des2, ret)
           print *,'description2 : ',des2
        endif

        call mfiodw(fid, MED_MESH_SUPPORT, smname1,
     &          '++un maillage support pour test34++', ret)
        if (ret .ne. 0 ) then
           print *,'Erreur inattendue d''écriture de la',
     &          ' description du maillage support'
        endif

C     ** creation d'un modèle d'éléments de structure **
        call msecre(fid,MED_PARTICLE_NAME, 3, MED_NO_MESHNAME,MED_NONE
     &              ,MED_NONE, mtype1, ret)
        if (ret .ne. 0 ) then
           print *,'Erreur inattendue d''écriture de l''',
     &          ' élément de structure'
        endif
        call mfiodw(fid, MED_ELSTRUCT, MED_PARTICLE_NAME,
     &              '++un élément de structure pour test34++', ret)
        if (ret .ne. 0 ) then
           print *,'Erreur inattendue d''écriture de la',
     &          ' description de l''élément de structure'
        endif

        
C     ** creation de la localisation des points de Gauss modèle n°1 **
        call mlclow(fid,gauss1_1,MED_TRIA6,2,refcoo1,MED_FULL_INTERLACE,
     &              ngauss1_1,gscoo1_1, wg1_1,MED_NO_INTERPOLATION,
     &              MED_NO_MESH_SUPPORT, ret)
        print *,ret
        if (ret .ne. 0 ) then
           print *,'Erreur à la création du modèle n°1 : ', gauss1_1
           call efexit(-1)
        endif
        des1="une localisation de points d'intégration pour test34"
        call mfiodw(fid, MED_LOCALIZATION, gauss1_1,
     &              des1, ret)
        if (ret .ne. 0 ) then
           print *,'Erreur inattendue d''écriture de la',
     &          ' description de la localisation : ',gauss1_1
        endif

    
C     ** Creation de profil
C     ** - qui selectionne uniquement le 2e element du tableau valr1
        call mpfprw(fid,nomprofil1,1,profil1,ret)
        print *,ret
        if (ret .ne. 0 ) then
           print *,'Erreur à la création du profil : ', nomprofil1
           call efexit(-1)
        endif
        des1='un profil de champ pour test34'
        call mfiodw(fid, MED_PROFILE, nomprofil1,
     &              des1, ret)
        if (ret .ne. 0 ) then
           print *,'Erreur inattendue d''écriture de la',
     &          ' description de profil : ',nomprofil1
        endif


C     ** Fermeture du fichier *
        call mficlo(fid,ret)
        if (ret .ne. 0 ) then
           print *,'Erreur à la fermeture du fichier : '
           ret = -1
        endif   

        print *,"Le code retour : ",ret
        call efexit(ret)

        end 



