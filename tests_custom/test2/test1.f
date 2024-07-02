      subroutine mfivop(fid, name, access, major, minor, rel, cret)
c     DEC$ ATTRIBUTES DLLEXPORT :: mfivop
c
      implicit none
      save
      character *(*) name
      integer*8 fid
      integer   cret
      integer access
      integer major, minor, rel
      integer*8 mfifvop
      integer len_name  ! Local variable to hold length
c
c
c Debugging output
      print *, "Entering mfivop"
c Verify the content and address of the name variable
      print *, "Address of name variable: ", loc(name)
      print *, "name: '", name, "'"
c Apply len_trim and manage trailing spaces
      len_name = len_trim(name)
      print *, "len_name: ", len_name
      print *, "name after len_trim: '", name(1:len_name), "'"
c Get the trimmed length of the name
c Debugging output
      print *, "Exiting mfivop"
      return
      end