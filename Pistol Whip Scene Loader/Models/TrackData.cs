using System;
using System.Collections;
using System.Collections.Generic;

namespace Models
{

    public class TrackData
    {
        public LevelData level;

        public Difficulty difficulty;

        public List<BeatData> beats = new List<BeatData>();

        public List<float> beatTimes = new List<float>();

        public float sampleRate;

        public float playerSpeed = 3;

        public Koreography koreography;

        public string songName;
    
    }

    public enum Difficulty
    {
        Easy = 0,
        Normal = 1,
        Hard = 2,
        Expert = 3
    }
}
