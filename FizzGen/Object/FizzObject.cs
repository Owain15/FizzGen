using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FizzGen.Object
{
	public class FizzObject
	{
		public bool isPisyicsActive { get; set; }

		public (long x, long y) GridIndex {  get; set; }
		public (long x ,long y) Position { get; set; }
		public long Mass { get; set; }
		public (long x, long y) Valocity { get; set; }


		public FizzObject()
		{
			isPisyicsActive = false;

			GridIndex = (0,0);

			Position = (0, 0);

			Mass = 0;

			Valocity = (0, 0);
		
		}

	}
}
