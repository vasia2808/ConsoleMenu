using System;
using System.Collections.Generic;

namespace ConsoleMenu
{
    public class Menu
    {
        public class MenuItem
        {
            public string Name { get; set; }
            public event SelectEventHandler Select;

            public MenuItem(string name, SelectEventHandler handler)
            {
                Name = name;
                Select += handler;
            }

            public void OnSelected()
            {
                Select.Invoke(this);
            }
        }

        #region Constats

        private const int ITEMS_LIST_POSITION = 2;
        private readonly List<MenuItem> items = new List<MenuItem>();

        #endregion

        #region Fields

        public delegate void SelectEventHandler(MenuItem item);
        private int _arrowPosition = 0;

        #endregion

        #region Properties

        private int ArrowPosition
        {
            get { return _arrowPosition; }
            set
            {
                ClearArrow();
                _arrowPosition = (items.Count + value) % items.Count; ;
                PrintArrow();
            }
        }

        public string HeaderText { get; set; }
        public char LineChar { get; set; } = '-';
        public string Arrow { get; set; } = " => ";

        #endregion

        public void Add(string name, SelectEventHandler handler)
        {
            items.Add(new MenuItem(name, handler));
        }

        public void Show()
        {
            OnShown();

            ConsoleKey key;

            do
            {
                key = Console.ReadKey().Key;

                switch (key)
                {
                    case ConsoleKey.Enter:
                        {
                            OnSelected();

                            OnShown();
                            break;
                        }

                    case ConsoleKey.UpArrow:
                        ArrowMoveUp();
                        break;

                    case ConsoleKey.DownArrow:
                        ArrowMoveDown();
                        break;
                }
            } while (key != ConsoleKey.Escape);

            OnExited();
        }

        private void OnShown()
        {
            Console.Clear();
            Console.CursorVisible = false;
            PrintMenu();
        }

        private void OnSelected()
        {
            items[ArrowPosition].OnSelected();
        }

        private void OnExited()
        {
            Console.Clear();
            Console.CursorVisible = true;
        }

        private void PrintMenu()
        {
            PrintHeader();
            PrintItems();
            PrintArrow();
        }

        private void PrintHeader()
        {
            Console.WriteLine("".PadRight(Arrow.Length) + HeaderText);
            PrintLine(1);
        }

        private void PrintItems()
        {
            foreach (MenuItem item in items)
            {
                Console.WriteLine("".PadRight(Arrow.Length) + item.Name);
            }
        }

        private void PrintLine(int position)
        {
            Console.SetCursorPosition(0, position);

            for (int i = 0; i < Console.WindowWidth - 1; i++)
            {
                Console.Write(LineChar);
            }

            Console.WriteLine();
        }

        private void ArrowMoveUp()
        {
            ArrowPosition--;
        }

        private void ArrowMoveDown()
        {
            ArrowPosition++;
        }

        private void PrintArrow()
        {
            Console.SetCursorPosition(0, ArrowPosition + ITEMS_LIST_POSITION);
            Console.WriteLine(Arrow);
        }

        private void ClearArrow()
        {
            Console.SetCursorPosition(0, ArrowPosition + ITEMS_LIST_POSITION);
            Console.Write("".PadRight(Arrow.Length));
        }
    }
}
