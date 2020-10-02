using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;


namespace Models
{
	public class SplitRooftopSection : TrackSection
	{
		public override int section { get { return 8; } }

		public int laneWidth;
		public bool solidLane;
		public bool leftDebris;
		public Debris leftDebrisSettings;
		public int leftGroundHeight;
		public int leftBuildingMinDistance;
		public int leftBuildingMaxDistance;
		public int leftBuildingFloorHeight;
		public int leftBuildingMinFloors;
		public int leftBuildingMaxFloors;
		public int leftBuildingMinLength;
		public int leftBuildingMaxLength;
		public int leftBuildingMinDepth;
		public int leftBuildingMaxDepth;
		public int leftMinorCrossMin;
		public int leftMinorCrossMax;
		public int leftMajorCrossInterval;
		public int leftMajorCrossMin;
		public int leftMajorCrossMax;
		public EWallDecorator _leftInnerWallDecorator;
		public EWallDecorator _leftLeadingWallDecorator;
		public EGroundDecorator _leftGroundDecorator;
		public EGroundDecorator _leftAlleyDecorator;
		public EGroundDecorator _leftRooftopDecorator;
		public EGroundDecorator _leftLaneDecorator;
		public int leftAlleyDecorationDepth;
		public int leftBuildingDecorationDepth;
		public bool leftDecorateDeepBuildings;
		public bool rightDebris;
		public Debris rightDebrisSettings;
		public int rightGroundHeight;
		public int rightBuildingMinDistance;
		public int rightBuildingMaxDistance;
		public int rightBuildingFloorHeight;
		public int rightBuildingMinFloors;
		public int rightBuildingMaxFloors;
		public int rightBuildingMinLength;
		public int rightBuildingMaxLength;
		public int rightBuildingMinDepth;
		public int rightBuildingMaxDepth;
		public int rightMinorCrossMin;
		public int rightMinorCrossMax;
		public int rightMajorCrossInterval;
		public int rightMajorCrossMin;
		public int rightMajorCrossMax;
		public EWallDecorator _rightInnerWallDecorator;
		public EWallDecorator _rightLeadingWallDecorator;
		public EGroundDecorator _rightGroundDecorator;
		public EGroundDecorator _rightAlleyDecorator;
		public EGroundDecorator _rightRooftopDecorator;
		public EGroundDecorator _rightLaneDecorator;
		public int rightAlleyDecorationDepth;
		public int rightBuildingDecorationDepth;
		public bool rightDecorateDeepBuildings;
		public List<BlockRange> leftBuildings;
		public List<BlockRange> leftAlleys;
		public List<BlockRange> rightBuildings;
		public List<BlockRange> rightAlleys;
	}
}