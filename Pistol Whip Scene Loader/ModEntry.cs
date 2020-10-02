using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Harmony;
using MelonLoader;

namespace Pistol_Whip_Scene_Loader
{
    public class ModEntry : MelonMod
    {

        [HarmonyPatch(typeof(SongSelectionUIController), "Awake", new System.Type[0] { })]
        public static class SongSelectionUIController_Start
        {
            public static void Postfix(SongSelectionUIController _instance)
            {
                MelonLogger.Log("SongSelectionUIController.start called");
            }
        }

        [HarmonyPatch(typeof(SongPanelUIController), "OnClick", new System.Type[0] { })]
        public static class SongPanelUIController_OnClick
        {
            public static void Prefix(SongPanelUIController _instance)
            {

            }
        }

        [Harm]
    }
}
