using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Models
{
	public class HallwaySection : TrackSection
	{
		public override int section { get { return 4; } }

		public int centerWidthMin;
		public int centerWidthMax;
		public int centerHeightMin;
		public int centerHeightMax;
		public int crossWidthMin;
		public int crossWidthMax;
		public int crossIntervalMin;
		public int crossIntervalMax;
		public int crossHeightMin;
		public int crossHeightMax;
		public int crossDepthMin;
		public int crossDepthMax;
		public bool symmetrical;
	}
}