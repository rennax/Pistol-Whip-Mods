using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Models
{
	public class RoomSection : TrackSection
	{
		public override int section { get { return 3; } }

		public int roomWidthMin;
		public int roomWidthMax;
		public int roomLengthMin;
		public int roomLengthMax;
		public int roomHeightMin;
		public int roomHeightMax;
		public int roomShuffleMax;
		public int spacerMinLength;
		public int spacerMaxLength;
		public int spacerMinWidth;
		public int spacerMaxWidth;
		public int spacerMinHeight;
		public int spacerMaxHeight;

		public int propBorderWidth;
		public EWallDecorator _wallDecorator;
		public EGroundDecorator _edgeDecorator;
		public EGroundDecorator _groundDecorator;
		public List<BlockRange> rooms;
	}
}