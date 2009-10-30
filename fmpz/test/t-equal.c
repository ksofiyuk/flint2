/*============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

===============================================================================*/
/****************************************************************************

   Copyright (C) 2009 William Hart

*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "ulong_extras.h"
#include "fmpz.h"

int main(void)
{
   int result;
   printf("equal....");
   fflush(stdout);

   fmpz_randinit();

   for (ulong i = 0; i < 100000UL; i++) 
   {
      fmpz_t a, b;
      
      fmpz_init(a);
      fmpz_init(b);

      fmpz_randtest(a, 200);
      
      fmpz_set(b, a);
      result = (fmpz_equal(a, b));
      
      if (!result)
      {
         printf("FAIL\n");
         printf("a = "); fmpz_print(a); printf("\n");
         printf("b = "); fmpz_print(b); printf("\n");
         abort();
      }

      fmpz_clear(a);
      fmpz_clear(b);
   }

   for (ulong i = 0; i < 100000UL; i++) 
   {
      fmpz_t a, b;
      mpz_t c, d;
      
      fmpz_init(a);
      fmpz_init(b);

      mpz_init(c);
      mpz_init(d);

      fmpz_randtest(a, 200);
      fmpz_randtest(b, 200);
      
      fmpz_get_mpz(c, a);
      fmpz_get_mpz(d, b);

      result = (fmpz_equal(a, b) == (mpz_cmp(c, d) == 0));

      if (!result)
      {
         printf("FAIL\n");
         gmp_printf("c = %Zd, d = %Zd\n", c, d);
         abort();
      }

      fmpz_clear(a);
      fmpz_clear(b);

      mpz_clear(c);
      mpz_clear(d);
   }

   fmpz_randclear();

   _fmpz_cleanup();
   printf("PASS\n");
   return 0;
}
