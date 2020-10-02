
using System;
using System.Collections;
using System.Collections.Generic;


namespace Models
{
    public class ObstacleData
    {

        public Placement placement;

        public ObstacleType type;

        public enum Placement
        {
            EvenMoreLeft = -3,
            FarLeft = -2,
            Left = -1,
            Center = 0,
            Right = 1,
            FarRight = 2,
            EvenMoreRight = 3
        }

        public enum ObstacleType
        {
            Sidestep = 0,
            LimboTall = 1,
            LimboShort = 2,
        }
    }
}