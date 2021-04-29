using System;

namespace ConsoleMenu
{
    public class MainMenu : Menu
    {
        public MainMenu()
        {
            HeaderText = "Main Menu";

            Add("Print \"Hellow World\"", PrintHelloWorld);
            Add("Print this item name", ThisItemName);
        }

        private delegate void WrapHandler();

        private void Wrapper(WrapHandler handler)
        {
            Console.Clear();
            Console.CursorVisible = true;

            handler();

            Console.WriteLine();
            Console.WriteLine("Press any key to continue!");
            Console.ReadKey();
        }

        private void PrintHelloWorld(MenuItem sender)
        {
            Wrapper(() =>
            {
                Console.WriteLine("Hello world");
            });
        }

        private void ThisItemName(MenuItem sender)
        {
            Wrapper(() =>
            {
                Console.WriteLine(sender.Name);
            });
        }
    }
}
