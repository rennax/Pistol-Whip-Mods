using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Models
{
	public class RooftopSection : TrackSection
	{
		public override int section { get { return 7; } }

		public int laneWidth;
		public bool solidLane;
		public int buildingMinDistance;
		public int buildingMaxDistance;
		public int buildingFloorHeight;
		public int buildingMinFloors;
		public int buildingMaxFloors;
		public int buildingMinLength;
		public int buildingMaxLength;
		public int buildingMinDepth;
		public int buildingMaxDepth;
		public int minorCrossMin;
		public int minorCrossMax;
		public int majorCrossInterval;
		public int majorCrossMin;
		public int majorCrossMax;
		public bool symmetrical;
		public EWallDecorator _innerWallDecorator;
		public EWallDecorator _leadingWallDecorator;
		public EGroundDecorator _groundDecorator;
		public EGroundDecorator _alleyDecorator;
		public EGroundDecorator _rooftopDecorator;
		public EGroundDecorator _laneDecorator;
		public int alleyDecorationDepth;
		public int buildingDecorationDepth;
		public bool decorateDeepBuildings;
		public List<BlockRange> buildings;
		public List<BlockRange> alleys;
	}
}