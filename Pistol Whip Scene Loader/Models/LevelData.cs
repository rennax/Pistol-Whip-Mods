using Newtonsoft.Json;
using System.Collections;
using System.Collections.Generic;

namespace Models
{
	public class LevelData
	{
	    [JsonProperty]
		public string songName;
		[JsonProperty]
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

	public class LevelPacker
	{
		public string version;
		public AlbumArtMetadata albumArtMetadata;
		public LevelData levelData;
	}

    public class AlbumArtMetadata
    {
        public LevelData level;

        [JsonProperty]
        public string songArtists;
        [JsonProperty]
        public string songName;
        [JsonProperty]
        public string tempo;

        public string art;



        [JsonProperty]
        private const bool artIsWIP = false;
        [JsonProperty]
        public Vector2i imgSize;



    }
}