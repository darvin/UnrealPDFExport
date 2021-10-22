BEGIN_DEFINE_SPEC(SampleSpecTest, "PDFExport.PDFExport.Tests.SampleSpecTest",
EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
int UsefulInteger = 0;
void UtilityMethodForTest();
END_DEFINE_SPEC(SampleSpecTest)

void SampleSpecTest::UtilityMethodForTest()
{
	// do stg 
}

void SampleSpecTest::Define()
{
	It("Test description", [this]()
	{
		const auto a = true;
		TestTrue("value of a", a);
	});

	BeforeEach([this]()
	{
		UE_LOG(LogTemp, Display, TEXT("b1"));
	});
	Describe("Scope1", [this]()
	{
		BeforeEach([this]()
		{
			UE_LOG(LogTemp, Display, TEXT("b2"));
		});

		It("Test1", [this]()
		{
			UE_LOG(LogTemp, Display, TEXT("t1"));
		});

		Describe("Scope2", [this]()
		{
			BeforeEach([this]()
			{
				UE_LOG(LogTemp, Display, TEXT("b3"));
			});

			It("Test2", [this]()
			{
				UE_LOG(LogTemp, Display, TEXT("t23"));
			});

			It("Test3", [this]()
			{
				UE_LOG(LogTemp, Display, TEXT("t23"));
			});

			AfterEach([this]()
			{
				UE_LOG(LogTemp, Display, TEXT("a1"));
			});
		});

		AfterEach([this]()
		{
			UE_LOG(LogTemp, Display, TEXT("a2"));
		});

		AfterEach([this]()
		{
			UE_LOG(LogTemp, Display, TEXT("a3"));
		});
	});

	AfterEach([this]()
	{
		UE_LOG(LogTemp, Display, TEXT("a4"));
	});
}