using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Linq;

namespace Models
{
    public class EnemySequence
    {
//        public GameObject actionHolder;

        public CheevoID forceCheevoID;

        public List<EnemyAction> actions = new List<EnemyAction>();

        public float playerActionLerp = 0f;

        public bool autospawn = true;

        public bool isThreat;

        public float duration = 0;


    }

}
