program hello
    use subroutines, only: call_me
    implicit none
    character(len=255) :: kfic
    character(len=200) :: nofimd

    kfic = 'fort.80                                                                                                                                                                                                                                                        '
    ! Initialize the variable 'nofimd'
    nofimd = kfic(1:200)
!    nofimd = 'Hello, this is a test string.'

    ! Print diagnostic message
    print *, 'Before calling subroutine'

    ! Call the subroutine
    call call_me(nofimd)

    ! Print diagnostic message
    print *, 'After calling subroutine'
end program hello
