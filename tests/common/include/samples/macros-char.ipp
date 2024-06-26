#define ASSERT_ALL_SAMPLES_IMPL(R, DATA, ELEM) \
	DATA(ELEM)

#define ASSERT_ALL_SAMPLES(ASSERTER)                                                                                                              \
	{                                                                                                                                             \
		BOOST_PP_SEQ_FOR_EACH(ASSERT_ALL_SAMPLES_IMPL, ASSERTER, ADAPTOR_SAMPLES BASIC_SAMPLES COMPOUND_SAMPLES DIVERGENT_SAMPLES REPEAT_SAMPLES) \
	} REQUIRE_SEMICOLON



#define ASSERT_ALL_SAMPLES_2_EXPAND(ELEM1) \
	ELEM1, IDENTITY

#define ASSERT_ALL_SAMPLES_2_IMPL(r, product) \
	(ASSERT_ALL_SAMPLES_2_EXPAND product)

// This macro needs to be manually expanded in this ugly way otherwise it crashes the compiler
#define ASSERT_ALL_SAMPLES_2(ASSERTER)                                                                                      \
	{                                                                                                                       \
		IDENTITY(BOOST_PP_SEQ_FOR_EACH_PRODUCT(ASSERTER ASSERT_ALL_SAMPLES_2_IMPL, (ADAPTOR_SAMPLES)(ADAPTOR_SAMPLES)))     \
		IDENTITY(BOOST_PP_SEQ_FOR_EACH_PRODUCT(ASSERTER ASSERT_ALL_SAMPLES_2_IMPL, (ADAPTOR_SAMPLES)(BASIC_SAMPLES)))       \
		IDENTITY(BOOST_PP_SEQ_FOR_EACH_PRODUCT(ASSERTER ASSERT_ALL_SAMPLES_2_IMPL, (ADAPTOR_SAMPLES)(COMPOUND_SAMPLES)))    \
		IDENTITY(BOOST_PP_SEQ_FOR_EACH_PRODUCT(ASSERTER ASSERT_ALL_SAMPLES_2_IMPL, (ADAPTOR_SAMPLES)(DIVERGENT_SAMPLES)))   \
		IDENTITY(BOOST_PP_SEQ_FOR_EACH_PRODUCT(ASSERTER ASSERT_ALL_SAMPLES_2_IMPL, (ADAPTOR_SAMPLES)(REPEAT_SAMPLES)))      \
		IDENTITY(BOOST_PP_SEQ_FOR_EACH_PRODUCT(ASSERTER ASSERT_ALL_SAMPLES_2_IMPL, (BASIC_SAMPLES)(ADAPTOR_SAMPLES)))       \
		IDENTITY(BOOST_PP_SEQ_FOR_EACH_PRODUCT(ASSERTER ASSERT_ALL_SAMPLES_2_IMPL, (BASIC_SAMPLES)(BASIC_SAMPLES)))         \
		IDENTITY(BOOST_PP_SEQ_FOR_EACH_PRODUCT(ASSERTER ASSERT_ALL_SAMPLES_2_IMPL, (BASIC_SAMPLES)(COMPOUND_SAMPLES)))      \
		IDENTITY(BOOST_PP_SEQ_FOR_EACH_PRODUCT(ASSERTER ASSERT_ALL_SAMPLES_2_IMPL, (BASIC_SAMPLES)(DIVERGENT_SAMPLES)))     \
		IDENTITY(BOOST_PP_SEQ_FOR_EACH_PRODUCT(ASSERTER ASSERT_ALL_SAMPLES_2_IMPL, (BASIC_SAMPLES)(REPEAT_SAMPLES)))        \
		IDENTITY(BOOST_PP_SEQ_FOR_EACH_PRODUCT(ASSERTER ASSERT_ALL_SAMPLES_2_IMPL, (COMPOUND_SAMPLES)(ADAPTOR_SAMPLES)))    \
		IDENTITY(BOOST_PP_SEQ_FOR_EACH_PRODUCT(ASSERTER ASSERT_ALL_SAMPLES_2_IMPL, (COMPOUND_SAMPLES)(BASIC_SAMPLES)))      \
		IDENTITY(BOOST_PP_SEQ_FOR_EACH_PRODUCT(ASSERTER ASSERT_ALL_SAMPLES_2_IMPL, (COMPOUND_SAMPLES)(COMPOUND_SAMPLES)))   \
		IDENTITY(BOOST_PP_SEQ_FOR_EACH_PRODUCT(ASSERTER ASSERT_ALL_SAMPLES_2_IMPL, (COMPOUND_SAMPLES)(DIVERGENT_SAMPLES)))  \
		IDENTITY(BOOST_PP_SEQ_FOR_EACH_PRODUCT(ASSERTER ASSERT_ALL_SAMPLES_2_IMPL, (COMPOUND_SAMPLES)(REPEAT_SAMPLES)))     \
		IDENTITY(BOOST_PP_SEQ_FOR_EACH_PRODUCT(ASSERTER ASSERT_ALL_SAMPLES_2_IMPL, (DIVERGENT_SAMPLES)(ADAPTOR_SAMPLES)))   \
		IDENTITY(BOOST_PP_SEQ_FOR_EACH_PRODUCT(ASSERTER ASSERT_ALL_SAMPLES_2_IMPL, (DIVERGENT_SAMPLES)(BASIC_SAMPLES)))     \
		IDENTITY(BOOST_PP_SEQ_FOR_EACH_PRODUCT(ASSERTER ASSERT_ALL_SAMPLES_2_IMPL, (DIVERGENT_SAMPLES)(COMPOUND_SAMPLES)))  \
		IDENTITY(BOOST_PP_SEQ_FOR_EACH_PRODUCT(ASSERTER ASSERT_ALL_SAMPLES_2_IMPL, (DIVERGENT_SAMPLES)(DIVERGENT_SAMPLES))) \
		IDENTITY(BOOST_PP_SEQ_FOR_EACH_PRODUCT(ASSERTER ASSERT_ALL_SAMPLES_2_IMPL, (DIVERGENT_SAMPLES)(REPEAT_SAMPLES)))    \
		IDENTITY(BOOST_PP_SEQ_FOR_EACH_PRODUCT(ASSERTER ASSERT_ALL_SAMPLES_2_IMPL, (REPEAT_SAMPLES)(ADAPTOR_SAMPLES)))      \
		IDENTITY(BOOST_PP_SEQ_FOR_EACH_PRODUCT(ASSERTER ASSERT_ALL_SAMPLES_2_IMPL, (REPEAT_SAMPLES)(BASIC_SAMPLES)))        \
		IDENTITY(BOOST_PP_SEQ_FOR_EACH_PRODUCT(ASSERTER ASSERT_ALL_SAMPLES_2_IMPL, (REPEAT_SAMPLES)(COMPOUND_SAMPLES)))     \
		IDENTITY(BOOST_PP_SEQ_FOR_EACH_PRODUCT(ASSERTER ASSERT_ALL_SAMPLES_2_IMPL, (REPEAT_SAMPLES)(DIVERGENT_SAMPLES)))    \
		IDENTITY(BOOST_PP_SEQ_FOR_EACH_PRODUCT(ASSERTER ASSERT_ALL_SAMPLES_2_IMPL, (REPEAT_SAMPLES)(REPEAT_SAMPLES)))       \
	} REQUIRE_SEMICOLON
