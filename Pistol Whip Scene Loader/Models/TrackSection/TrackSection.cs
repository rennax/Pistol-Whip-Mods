using Newtonsoft.Json;
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;



namespace Models
{
    public class TrackSection
    {

        public virtual int section { get { return -1; } }
        public Color color;
        public Color fog;
        public Color glow;
        public Color enemy;


        public bool _customColors;
        public bool _customEnemyColor;
        public bool startingWall;
        public bool endingWall;
        public int height;
        public int groundHeight;
        public int start;
        public int end;
        public Vector3i min;
        public Vector3i max;
        public Vector3i extent;
        //Todo figure out debris
        public bool generateDebris = false;
        public Debris debris;
        //public int propSeed; 
        public int yStep;
        public int zStep;
        public int[] yOffsets;
        public int[] zOffsets;
        //public Block[] blocks;
        public Vector3i size;
        public HashSet<Vector3i> emptyBlocks; //is empty it seems;
        public HashSet<Vector3i> decorationBlocks; //is empty it seems;
        public List<WorldObject> props; //is empty it seems;
        public Vector3i lastDebrisPoint;
    }



    public struct ColorMock
    {
        public float r;
        public float g;
        public float b;
        public float a;
        public ColorMock(Color c)
        {
            r = c.r;
            g = c.g;
            b = c.b;
            a = c.a;
        }
    }


    [Serializable]
    public struct Debris
    {
        //public int seed;
        public Debris.Distribution distribution;
        public Debris.Projection projection;
        public Debris.Spread spread;
        public float density;
        public Vector2i interval;
        public float uniformity;
        public Vector3i minSize;
        public Vector3i maxSize;
        public Debris.Shape shape;
        public bool buildOnAir;
        public Debris.Timing timing;

        public enum Distribution
        {
            Ground = 0,
            PlayerLevel = 1,
            Projected = 2,
        }

        public enum Projection
        {
            Down = 0,
            Outward = 1,
            Forward = 2,
            Up = 3,
        }

        public enum Spread
        {
            Random = 0,
            Spread = 1,
        }

        public enum Shape
        {
            Cube = 0,
            Pile = 1
        }

        public enum Timing
        {
            Normal = 0,
            AfterRegions = 1,
        }
    }
}