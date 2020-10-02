using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Models
{
	public struct BlockRange
	{
		public Vector3i min;
		public Vector3i max;
	}

	public enum EWallDecorator
	{
		None = 0,
		Chinatown_Alley_Wall_Decorator = 1306332334,
		Cyberpunk_Wall_Decorator = 333955942,
		Cyberpunk_fronts = -240418552,
		Cyberpunk_Interior_Fronts = 1591180449,
		Cyberpunk_Interior_Sides = 1357552855,
		Cyberpunk_Wall_NoGround = 1707659857,
		Cyberpunk_Wall_neg40Ground = -1335811706,
		Death_Streets_InnerWalls = 1484116929,
		Death_Streets_LeadingWalls = 1965851391,
		Death_Nightmare_InnerWalls = -275909130,
		Death_Nightmare_LeadingWalls = 1649407904,
		Cyberpunk_fronts_NoGround = -1484571295,
		NeoTokyo_Fronts = -358961437,
		NeoTokyo_Wall_Decorator = 904820003,
		NeoTokyo_Wall_GroundOnly_Decorator = -339785187,
		NeoTokyo_Wall_UpperOnly_Decorator = -454074896
	}

	[Serializable]
	public class AlleySection : TrackSection
	{
		public override int section { get { return 2; } }

		public int laneMinWidth;
		public int laneMaxWidth;
		public int buildingFloorHeight;
		public int buildingMinFloors;
		public int buildingMaxFloors;
		public int buildingMinLength;
		public int buildingMaxLength;
		public int minorCrossMin;
		public int minorCrossMax;
		public int majorCrossInterval;
		public int majorCrossMin;
		public int majorCrossMax;
		public bool symmetrical;
		public EWallDecorator _wallDecorator;
		public EGroundDecorator _groundDecorator;
		public EGroundDecorator _alleyDecorator;
		public int alleyDecorationDepth;
		private List<BlockRange> buildings;
		private List<BlockRange> alleys;
	}
}