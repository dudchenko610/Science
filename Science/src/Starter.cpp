#pragma once

#include <iostream>
#include <locale>
#include <thread>

#include <GL/glew.h>
#include <GLFW/glfw3.h>



#include "app/Initializer.cpp"
#include "initializer/Initializer.h"
#include "app/App.h"



#include "store/Store.h"

#include "windows/test-ui-window/TestUIWindow.h"

#include "collections/avl-tree/AVLTree.h"
#include "collections/avl-tree/TreePrinter.h"

#include "Tree.h"

#include "move_example.h"

#include "common/multithreading/spinlock_mutex/spinlock_mutex.h"
#include "common/variadic-struct/Tuple.h"

#include "collections/avl-tree-duplicates/AVLTreeDuplicates.h"

//#include "ChernoMoveExample.h"


struct M
{
	M() = default;
	M(int index) : index(index), size(0)
	{
	}

	M(int index, int size) : index(index), size(size)
	{
	}

	int index;
	int size;

};


//mthreading::spinlock_mutex mutex;
//
//void func()
//{
//	std::lock_guard<mthreading::spinlock_mutex> lg(mutex);
//
//	std::cout << std::this_thread::get_id() << " hello" << std::endl;
//	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
//}
//
//void func2()
//{
//	if (mutex.try_lock())
//	{
//		std::cout << std::this_thread::get_id() <<  " func2 locked" << std::endl;
//		mutex.unlock();
//	}
//	else
//	{
//		std::cout << std::this_thread::get_id() << " func2 is not locked" << std::endl;
//	}
//
//	std::cout << std::this_thread::get_id() << " func2 FINISH" << std::endl;
//
//}
//
//void func3()
//{
//	mutex.lock();
//	
//	std::cout << std::this_thread::get_id() << " func3 locked" << std::endl;
//
//	mutex.unlock();
//
//	std::cout << std::this_thread::get_id() << " func3 FINISH" << std::endl;
//
//}

template<typename... T>
void func4(T... args)
{
	std::cout << std::endl;
	std::cout << std::endl;


	std::cout << sizeof(core::Tuple<T...>) << std::endl;

	core::Tuple<T...> t(args...);

	std::cout << t.get<0>() << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
}


int main()
{
	setlocale(0, "RUS");



	std::cout << sizeof(core::Tuple<int, int, int, int, int, int, double>) << std::endl;

//	core::Tuple<double, int, int, int, int, int, int, int> y(1.0,2,3,4,5,6,7,8);

	//y.rest.rest.rest.rest.rest.rest.rest.rest.


	func4(1, 2, 3, 4, 5, 6, 7, 8.8);
	
/*

	collection::AVLTree<M> _avlTree(
		[](M& v) 
		{
			return v.index;
		}
	);



	_avlTree.Insert({ 40, 1 });
	_avlTree.Insert({ 40, 2 });

	treeprinter::TreePrinter<M>::Print(_avlTree.root, _avlTree.Height());

	_avlTree.Insert({ 50, 1 });
	_avlTree.Insert({ 50, 2 });

	treeprinter::TreePrinter<M>::Print(_avlTree.root, _avlTree.Height());


	collection::AVLTree<M> _avlTree2;

	std::cout << "Before move" << std::endl;

	_avlTree2 = std::move(_avlTree);

	treeprinter::TreePrinter<M>::Print(_avlTree2.root, _avlTree2.Height());


	_avlTree2.Remove({50, 1});
	treeprinter::TreePrinter<M>::Print(_avlTree2.root, _avlTree2.Height());

	_avlTree2.Remove({50, 2});
	treeprinter::TreePrinter<M>::Print(_avlTree2.root, _avlTree2.Height());


	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Finish" << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;


	collection::AVLTreeDuplicates<M> avlTree(
		4,
		[](M& v)
		{
			return v.index;
		},
		[](M& v)
		{
			return v.size;
		}

	);

	/*
	//move_example::test_it();
	
	{
		//collection::AVLTree<M> avlTree(
		//	[](M& v) 
		//	{
		//		return v.index;
		//	}
		//);

		std::cout << "AVLTree InsertED " << std::endl;

		avlTree.Insert({ 40, 1 });
		avlTree.Insert({ 40, 2 });

		treeprinter::TreePrinter<collection::BucketHolder<M>>::Print(avlTree.root, avlTree.Height());


		avlTree.Insert({ 50, 1 });
		avlTree.Insert({ 50, 2 });

		treeprinter::TreePrinter<collection::BucketHolder<M>>::Print(avlTree.root, avlTree.Height());


		avlTree.Insert({ 30, 1 });
		avlTree.Insert({ 30, 2 });

		treeprinter::TreePrinter<collection::BucketHolder<M>>::Print(avlTree.root, avlTree.Height());


		avlTree.Remove({ 40, 1 });
		avlTree.Remove({ 40, 2 });

		treeprinter::TreePrinter<collection::BucketHolder<M>>::Print(avlTree.root, avlTree.Height());


		avlTree.Remove({ 50, 1 });
		avlTree.Remove({ 50, 2 });

		treeprinter::TreePrinter<collection::BucketHolder<M>>::Print(avlTree.root, avlTree.Height());

		*/




/*
		collection::AVLTreeDuplicates<M> avlTree(
			4,
			[](M& v)
			{
				return v.index;
			},
			[](M& v)
			{
				return v.size;
			}

		);

		avlTree.Insert({ 40, 1 });
		avlTree.Insert({ 40, 2 });

		std::cout << "ALLOCATED SIZE = " << avlTree.AllocatedSize() << std::endl;
		treeprinter::TreePrinter<collection::BucketHolder<M>>::Print(avlTree.root, avlTree.Height());


		avlTree.Insert({ 50, 1 });
		avlTree.Insert({ 50, 2 });

		std::cout << "ALLOCATED SIZE = " << avlTree.AllocatedSize() << std::endl;
		treeprinter::TreePrinter<collection::BucketHolder<M>>::Print(avlTree.root, avlTree.Height());


		avlTree.Insert({ 30, 1 });
		avlTree.Insert({ 30, 2 });

		std::cout << "ALLOCATED SIZE = " << avlTree.AllocatedSize() << std::endl;
		treeprinter::TreePrinter<collection::BucketHolder<M>>::Print(avlTree.root, avlTree.Height());


		avlTree.Remove({ 40, 1 });
		avlTree.Remove({ 40, 2 });

		std::cout << "ALLOCATED SIZE = " << avlTree.AllocatedSize() << std::endl;
		treeprinter::TreePrinter<collection::BucketHolder<M>>::Print(avlTree.root, avlTree.Height());


		avlTree.Remove({ 50, 1 });
		avlTree.Remove({ 50, 2 });

		std::cout << "ALLOCATED SIZE = " << avlTree.AllocatedSize() << std::endl;
		treeprinter::TreePrinter<collection::BucketHolder<M>>::Print(avlTree.root, avlTree.Height());

		avlTree.Insert({ 60, 1 });
		avlTree.Insert({ 60, 2 });

		std::cout << "ALLOCATED SIZE = " << avlTree.AllocatedSize() << std::endl;
		treeprinter::TreePrinter<collection::BucketHolder<M>>::Print(avlTree.root, avlTree.Height());

		avlTree.Insert({ 70, 1 });
		avlTree.Insert({ 70, 2 });

		std::cout << "ALLOCATED SIZE = " << avlTree.AllocatedSize() << std::endl;
		treeprinter::TreePrinter<collection::BucketHolder<M>>::Print(avlTree.root, avlTree.Height());

		avlTree.Insert({ 80, 1 });
		avlTree.Insert({ 80, 2 });

		std::cout << "ALLOCATED SIZE = " << avlTree.AllocatedSize() << std::endl;
		treeprinter::TreePrinter<collection::BucketHolder<M>>::Print(avlTree.root, avlTree.Height());

		avlTree.Insert({ 90, 1 });
		avlTree.Insert({ 90, 2 });

		std::cout << "ALLOCATED SIZE = " << avlTree.AllocatedSize() << std::endl;
		treeprinter::TreePrinter<collection::BucketHolder<M>>::Print(avlTree.root, avlTree.Height());
		
		int c = 0;

		int input = 0;
		int b = 2;

		while (input != 1000)
		{
			c++;
			std::cin >> input;

			if (input == 500)
			{
				b++;
				continue;
			}
			int s;

			switch (b % 3)
			{
			case 0:
				std::cin >> s;
				avlTree.Insert(M(input, s));
				break;
			case 1:
				std::cin >> s;
				avlTree.Remove(M(input, s));
				break;
			case 2:
				M * bigger = avlTree.GetBigger(M(input));
				M * smaller = avlTree.GetSmaller(M(input));

				std::cout << "bigger = " << (bigger == nullptr ? 0xffffffff : bigger->index) << std::endl;
				std::cout << "smaller = " << (smaller == nullptr ? 0xffffffff : smaller->index) << std::endl;
				break;
			}

			std::cout << "SIZE = " << avlTree.Size() << std::endl;
			std::cout << "ALLOCATED SIZE = " << avlTree.AllocatedSize() << std::endl;

			treeprinter::TreePrinter<collection::BucketHolder<M>>::Print(avlTree.root, avlTree.Height());
		}

	//}
	

	std::cout << "AVLTree Destroyed " << std::endl;

	unsigned int ptr;
	glGenBuffers(1, &ptr);
	

	/*Der1 der;

	Der1* d = &der;

	Base2* b = reinterpret_cast<Base2*>(d);
	std::cout << "b2 = " << b->b << std::endl;

	Base2* b2 = dynamic_cast<Base2*>(d);
	


	//Der1* r = fnc<Der1*>(&der);

	fnc<void>();

	std::cout << "Base2* this = " << (int)b << std::endl;

	unsigned int ptr;
	glGenBuffers(1, &ptr);*/
	

	/*
	std::thread th1(func2);
	std::thread th2(func3);
	std::thread th3(func2);
	std::thread th4(func3);

	th1.join();
	th2.join();
	th3.join();
	th4.join();



	unsigned int ptr;
	glGenBuffers(1, &ptr);

	*/

	
	core::InitCore( [] () {} );
	uifb::InitCore( [] () {} );


	core::Store::Get();

	if (app::App::Get().InitGLFW() != 0)
	{

		unsigned int ptr;
		glGenBuffers(1, &ptr);

		return -1;
	}

	core::Window* wnd = mthreading::Thread::StartThread<test::TestUIWindow>(1000, 600);
	app::App::Get().Start(wnd);
	

	return 0;
}