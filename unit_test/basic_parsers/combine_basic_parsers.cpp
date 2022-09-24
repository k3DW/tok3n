#include "utility.h"

namespace k3::tok3n::tests::basic::combine
{

	constexpr OneChar<"abc"> oc1;
	constexpr OneChar<"bcd"> oc2;
	constexpr OneChar<"xyz"> oc3;
	constexpr NotChar<"abc"> nc1;
	constexpr NotChar<"bcd"> nc2;
	constexpr NotChar<"xyz"> nc3;

	void choice_OneChar()
	{
		assert
			, (oc1 | oc2) == (oc2 | oc1)
			, (oc1 | oc3) == (oc3 | oc1)
			, (oc2 | oc3) == (oc3 | oc2)
			, (oc1 | oc2) == OneChar<"abcd">{}
			, (oc1 | oc3) == OneChar<"abcxyz">{}
			, (oc2 | oc3) == OneChar<"bcdxyz">{}
			;
	}

	void choice_NotChar()
	{
		assert
			, (nc1 | nc2) == (nc2 | nc1)
			, (nc1 | nc3) == (nc3 | nc1)
			, (nc2 | nc3) == (nc3 | nc2)
			, (nc1 | nc2) == NotChar<"bc">{}
			, (nc1 | nc3) == OneChar<every_char>{}
			, (nc2 | nc3) == OneChar<every_char>{}
			;
	}

	void choice_OneChar_NotChar()
	{
		assert
			, (oc1 | nc1) == (nc1 | oc1)
			, (oc1 | nc2) == (nc2 | oc1)
			, (oc1 | nc3) == (nc3 | oc1)
			, (oc2 | nc1) == (nc1 | oc2)
			, (oc2 | nc2) == (nc2 | oc2)
			, (oc2 | nc3) == (nc3 | oc2)
			, (oc3 | nc1) == (nc1 | oc3)
			, (oc3 | nc2) == (nc2 | oc3)
			, (oc3 | nc3) == (nc3 | oc3)
			, (oc1 | nc1) == OneChar<every_char>{}
			, (oc1 | nc2) == NotChar<"d">{}
			, (oc1 | nc3) == NotChar<"xyz">{}
			, (oc2 | nc1) == NotChar<"a">{}
			, (oc2 | nc2) == OneChar<every_char>{}
			, (oc2 | nc3) == NotChar<"xyz">{}
			, (oc3 | nc1) == NotChar<"abc">{}
			, (oc3 | nc2) == NotChar<"bcd">{}
			, (oc3 | nc3) == OneChar<every_char>{}
			;
	}

	void not_OneChar_NotChar()
	{
		assert
			, !oc1 == nc1
			, !oc2 == nc2
			, !oc3 == nc3
			, !nc1 == oc1
			, !nc2 == oc2
			, !nc3 == oc3
			, !!oc1 == oc1
			, !!oc2 == oc2
			, !!oc3 == oc3
			, !!nc1 == nc1
			, !!nc2 == nc2
			, !!nc3 == nc3
			;
	}



	constexpr Literal<"literal"> l1;
	constexpr Literal<"ly"> l2;
	constexpr Literal<"test"> l3;

	void sequence_Literal()
	{
		assert
			, (l1 >> l2) == Literal<"literally">{}
			, (l1 >> l3) == Literal<"literaltest">{}
			, (l2 >> l1) == Literal<"lyliteral">{}
			, (l2 >> l3) == Literal<"lytest">{}
			, (l3 >> l1) == Literal<"testliteral">{}
			, (l3 >> l2) == Literal<"testly">{}
			;
	}

}