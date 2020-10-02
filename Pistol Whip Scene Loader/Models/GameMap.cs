using System.Collections;
using System.Collections.Generic;

namespace Models
{
	public class GameMap
	{
		public LevelData level;

		public TrackData trackData;

		public GeoSet geoSet;

		public bool isPlayable;

		public int enemyIgnoreCount;

		public int enemyHitIgnoreCount;

		public int enemyCount;

		public int rankedEnemyCount;

		public int hitCount;

		public int rankedHitCount;

		public int trueMaxScore;

		public int rankMaxScore;

		//public RankQuota[] rankQuotas;
	}
}
