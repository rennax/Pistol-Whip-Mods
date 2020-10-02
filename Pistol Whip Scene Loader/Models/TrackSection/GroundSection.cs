using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Models
{
    public enum EGroundDecorator
    {
        None = 0,
        Chinatown_Alley_Ground_Decorator = -175064445,
        Room_Edge_Ground_Decorator = 21553421,
        Room_Center_Ground_Decorator = 1853656057,
        Chinatown_Ground_Decorator = 1652850429,
        Cyberpunk_Ground_Decorator = 1374720925,
        Cyberpunk_CrossStreet_Decorator = -907079489,
        Cyberpunk_Interior_Tops = 1036193447,
        Cyberpunk_Interior_Floor = 1043209875,
        Cyberpunk_Rooftops = -139889710,
        Death_Streets_Ground = 820584051,
        Death_Nightmare_Ground = 542622820,
        Death_Streets_Rooftops = -283639398,
        Grave_Headstones_Ground = -1941308518,
        Grave_Mausoleums_Ground = 603619141,
        Grave_Ruins_Ground = 1206371717,
        Grave_Rooftops = -1290308170,
        Grave_Lane_Columns = -1331251706,
        Grave_Lane_Lamps = 258098258,
        Grave_Catacombs_Statues = -1048134331,
        Grave_Rooftops_TreesOnly = 1863934794,
        Grave_Lane_Candelabras = -576653717,
        Grave_Lane_Pews = 1524542942,
        HP_Forest = -1862087386,
        HP_Lane_Lamps = -450459295,
        HP_Lane_Columns = 272113843,
        NeoTokyo_Ground_Decorator = -2023880450
    }


    public class GroundSection : TrackSection
    {
        public override int section { get { return 6; } }
        public int laneWidth;
        public bool solidLane;
        public int decorationDistance;
        public EGroundDecorator _groundDecorator;
    }
}