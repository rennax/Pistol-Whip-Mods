using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Models
{
	public class OfficeSection : TrackSection
	{
		public override int section { get { return 5; } }

		public int centerWidthMin;
		public int centerWidthMax;
		public int centerHeightMin;
		public int centerHeightMax;
		public int officeWidthMin;
		public int officeWidthMax;
		public int officeIntervalMin;
		public int officeIntervalMax;
		public int officeHeightMin;
		public int officeHeightMax;
		public int officeDepthMin;
		public int officeDepthMax;
		public int doorMinWidth;
		public int doorMaxWidth;
		public int doorMinStart;
		public int doorMinEnd;
		public int doorHeight;
		public bool gapsAreHallways;
		public int minHallwayWidth;
		public int hallwayLength;
		public bool symmetrical;
		public int centerWidth;
		public int centerHeight;
		public int centerLeft;
		public int centerRight;
	}
}