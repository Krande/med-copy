module subroutines
    implicit none

contains
    subroutine call_me(nom)
        character(len=*), intent(in) :: nom

        ! Print diagnostic message
        print *, 'Inside subroutine'
        print *, 'The string passed is: ', trim(nom)
        ! len of string
        print *, 'The length of the string is: ', len(nom)

    end subroutine call_me
end module subroutines
