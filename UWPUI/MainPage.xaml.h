﻿//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace UWPUI
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

		void WriteNew();
		void AddToOpen();
		void Extract();
		void OpenArchive();
		void AddToList();
		void ConvertTo();


	};
}
