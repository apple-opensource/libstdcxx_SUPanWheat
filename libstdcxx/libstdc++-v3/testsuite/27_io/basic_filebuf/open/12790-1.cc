// Copyright (C) 2003 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 2, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING.  If not, write to the Free
// Software Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307,
// USA.

// 27.8.1.3 filebuf member functions

#include <locale>
#include <fstream>
#include <testsuite_hooks.h>
#include <testsuite_character.h>

// libstdc++/12790
void test01()
{
  using namespace std;
  using __gnu_test::character;
  typedef basic_filebuf<character>::traits_type traits_type;

  bool test __attribute__((unused)) = true;
  const char* name = "tmp_open_12790";

  locale loc(locale::classic(),
	     new codecvt<traits_type::char_type, char,
	     traits_type::state_type>);

  basic_filebuf<character> fb;
  fb.pubimbue(loc);

  fb.open(name, ios_base::out);
  fb.sputc(character::from_char('b'));
  fb.close();

  // Check that reopened basic_filebuf begins in the initial state.
  fb.open(name, ios_base::in);
  traits_type::int_type c = fb.sbumpc();
  VERIFY( c != traits_type::eof() );
  VERIFY( traits_type::eq(traits_type::to_char_type(c),
			  character::from_char('b')) );
  fb.close();
}

int main()
{
  test01();
  return 0;
}
