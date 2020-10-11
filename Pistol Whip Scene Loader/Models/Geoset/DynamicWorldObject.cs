using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Models
{
    public class DynamicWorldObject : WorldObject
    {
        public List<string> animationClipNames = new List<string>();
        public string animatorName;

        //For the LevelEventReceiver
        public string eventID;
        public ActionType actionType;
        //We set animator when loading it from assetbundle
        public string animatorProperty;
        public int animHash;

        public enum ActionType
        {
            UnityEvent = 0,
            AnimatorTrigger = 1,
            AnimatorBool = 2
        }
    }
}
