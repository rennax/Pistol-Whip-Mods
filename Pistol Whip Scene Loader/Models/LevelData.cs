using System.Collections;
using System.Collections.Generic;

namespace Models
{
	public class LevelData
	{
		public string songName;
		public float songLength;
		public string description;
		public GameMap[] gameMaps;
		public List<TrackSection> sections;
		public List<WorldVolume> volumes;
		public List<ColorShiftPoint> colors; //Might be calculated from sections
		public List<WorldObject> worldObjects;
		public List<WorldObject> simpleStaticWorldObjects;
		public List<WorldObject> simpleDynamicWorldObjects;
		public List<CullingRange> staticCullingRanges;
		public List<CullingRange> dynamicCullingRanges;
		public int obstacleSet;
		public int materialPropertiesSet;
		public int enemySet;
	}
}