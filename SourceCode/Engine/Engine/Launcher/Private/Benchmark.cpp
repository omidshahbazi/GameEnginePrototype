// Copyright 2012-2015 ?????????????. All Rights Reserved.
//
//#include <StringConverter.h>
//#include <CAllocationPolicy.h>
//#include <Windows.h>
//
//USING_NAMESPACE
//
//double BenchmarkWithSTDAllocator(uint32 Count)
//{
//	LARGE_INTEGER l1;
//	QueryPerformanceCounter(&l1);
//
//	List<BasicString<char, CAllocationPolicy>, CAllocationPolicy> list;
//	for (int32 i = 0; i < Count; i++)
//		list.Add("GameEngine");
//
//	list.Clear();
//
//	LARGE_INTEGER l2;
//	QueryPerformanceCounter(&l2);
//
//	LARGE_INTEGER freq;
//	QueryPerformanceFrequency(&freq);
//
//	return ((double)(l2.QuadPart - l1.QuadPart) / (double)freq.QuadPart);
//}
//
//double BenchmarkWithSackAllocator(uint32 Count)
//{
//	LARGE_INTEGER l1;
//	QueryPerformanceCounter(&l1);
//
//	List<String> list;
//	for (int32 i = 0; i < Count; i++)
//		list.Add("GameEngine");
//
//	list.Clear();
//
//	LARGE_INTEGER l2;
//	QueryPerformanceCounter(&l2);
//
//	LARGE_INTEGER freq;
//	QueryPerformanceFrequency(&freq);
//
//	return ((double)(l2.QuadPart - l1.QuadPart) / (double)freq.QuadPart);
//}
//
//void main()
//{
//	double result = 0;
//
//	const uint32 times = 5;
//
//	for (int i = 1; i <= times; i++)
//	{
//		uint32 count = 10;
//		for (int j = 1; j <= i; j++)
//			count *= 10;
//
//		double stackAllocator = BenchmarkWithSackAllocator(count);
//		double stdAllocator = BenchmarkWithSTDAllocator(count);
//		double res = stdAllocator / stackAllocator;
//
//		std::cout << "For " << count << ", StackAllocator is " << res << " times faster than STDAllocator based on with " << stackAllocator << " for StackAllocator and " << stdAllocator << " for STDAllocator\n\n";
//
//		result += res;
//	}
//
//	std::cout << "StackAllocator is ~" << (result / times) << " times faster than STDAllocator\n\n";
//
//
//
//	//
//	// Result #1
//	//
//	// AllocationPolicy
//	// 0.011733229327760341 on 1000
//	// 0.10556374471985058 on 10000
//	// 1.0401135890586459 on 100000
//	// 10.728508927765533 on 1000000
//
//	// StandardAllocationPolicy
//	// 0.038215406851870241 on 1000
//	// 0.59265547177887867 on 10000
//	// 6.3413603578773809 on 100000
//	// 57.245265487406883 on 1000000
//
//	//
//	// Result #2
//	//
//	//StackAllocator : 0.000869544 for 1000
//	//StackAllocator : 0.010653 for 10000
//	//StackAllocator : 0.0943365 for 100000
//	//StackAllocator : 0.936145 for 1000000
//
//	//STDAllocator : 0.0259494 for 1000
//	//STDAllocator : 0.657754 for 10000
//	//STDAllocator : 6.86842 for 100000
//	//STDAllocator : 67.6712 for 1000000
//
//
//	//
//	// Result #3
//	//
//	//For 100, StackAllocator is 6.07632 times faster than STDAllocator based on with 0.000114712 for StackAllocator and 0.000697026 for STDAllocator
//	//For 1000, StackAllocator is 30.549 times faster than STDAllocator based on with 0.000643293 for StackAllocator and 0.019652 for STDAllocator
//	//For 10000, StackAllocator is 77.2885 times faster than STDAllocator based on with 0.00647911 for StackAllocator and 0.500761 for STDAllocator
//	//For 100000, StackAllocator is 56.8586 times faster than STDAllocator based on with 0.0925388 for StackAllocator and 5.26162 for STDAllocator
//	//For 1000000, StackAllocator is 73.692 times faster than STDAllocator based on with 0.692641 for StackAllocator and 51.0421 for STDAllocator
//	//StackAllocator is ~48.8929 times faster than STDAllocator
//
//
//	//
//	// Result #4
//	//
//	//For 100, StackAllocator is 5.19279 times faster than STDAllocator based on with 0.00033508 for StackAllocator and 0.00174 for STDAllocator
//	//For 1000, StackAllocator is 18.7838 times faster than STDAllocator based on with 0.00273196 for StackAllocator and 0.0513164 for STDAllocator
//	//For 10000, StackAllocator is 74.3759 times faster than STDAllocator based on with 0.00648364 for StackAllocator and 0.482227 for STDAllocator
//	//For 100000, StackAllocator is 78.2449 times faster than STDAllocator based on with 0.0666926 for StackAllocator and 5.21836 for STDAllocator
//	//For 1000000, StackAllocator is 72.4764 times faster than STDAllocator based on with 0.68624 for StackAllocator and 49.7362 for STDAllocator
//	//StackAllocator is ~49.8148 times faster than STDAllocator
//
//	system("Pause");
//}
