using MelonLoader;
using System;
using System.Runtime;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;
using UnityEngine.UI;

using UnityEngine.Experimental;

using UnhollowerBaseLib;
using Harmony;
using Newtonsoft.Json;
using Il2CppSystem.Collections.Generic;
using TMPro;
using System.IO;
using SonicBloom.Koreo;

using System.Reflection;
using Il2CppSystem.Reflection;
using Il2CppSystem;
using System.Threading;
using System.Drawing;


/*
TODO List
-   Fix actions and enemy sequence so that they are not enabled by default.
    -   Hook and enable them while playing
        -   only if the current map is a custom map otherwise dont. Original enemy sequences are loaded from asset/resources.
-   Figure out how the rest of the enemy actions work
    -   Some of them refers to animation trigger hashes (Look towards dynamic objects)
-   Do backup of the koreoset before we overwrite for the custom map
-   Play song switch when selection the custom map. Currently this is not done.
-   LODSwitcher for dynamic and static props
-   Figure out how we store the personal best for a given custom song
 */


namespace Pistol_Whip_Scene_Loader
{
    public class ModEntry : MelonMod
    {
        CustomLevelDatabase database = new CustomLevelDatabase();

        public override void OnApplicationStart()
        {
            // Load configuration and overwrite any custom tracks
            MelonLogger.Log("OnApplicationStart called");
            MelonLogger.Log("Initializing custom level database");

            database.RebuildDatabase();
        }



        [HarmonyPatch(typeof(LevelDatabase), "BuildDictionaries", new System.Type[0])]
        public static class LevelDatabase_BuildDictionaries
        {
            
            public static void Postfix(LevelDatabase __instance)
            {
            }
        }
        

        [HarmonyPatch(typeof(SongSelectionUIController), "UpdateSelectedSong", new System.Type[1] { typeof(string) })]
        public static class SongSelectionUIController_SetStartUIPanelState
        {
            public static void Postfix(SongSelectionUIController __instance)
            {

                MelonLogger.Log("SongSelectionUIController.UpdateSelectedSong()");
                CustomLevelDatabase.AddPageIndicators(__instance);
                CustomLevelDatabase.PopulateSongSelectionUI(__instance);
            }
        }

        [HarmonyPatch(typeof(SongSelectionUIController), "Start", new System.Type[0])]
        public static class SongSelectionUIController_Start
        {
            public static void Postfix(SongSelectionUIController __instance)
            {
                MelonLogger.Log("SongSelectionUIController.Start()");
            }
        }


        [HarmonyPatch(typeof(SongPanelUIController), "OnClick", new System.Type[0])]
        public static class SongPanelUIController_OnClick
        {
            static bool firstClick = true;
            public static bool Prefix(SongPanelUIController __instance)
            {
                /* TODO
                - Preview play of song
                */
                MelonLogger.Log($"SongPanelUIController.OnClick called, with level index {__instance.levelDataIndex}");
                if (__instance.levelDataIndex > 19)
                {
                    //if no other song has bee clicked, find the song info panel + start button and enable it
                    if (firstClick)
                    {
                        MelonLogger.Log("First panel clicked in custom song\nEnable song info and start button manually");
                        __instance.parent.startSongUIButton.SetActive(true);
                        GameObject gameObject = GameObject.Find("/Managers/UI State Controller/PF_CHUI_AnchorPt_SongSelection/PF_SongSelectionCanvas_UIv2/PF_SongInfoCanvas_UIv2/PW_VerticalLayoutElementPanel");
                        //MelonLogger.Log(gameObject.name);
                        for (int i = 0; i < gameObject.transform.childCount; i++)
                        {
                            gameObject.transform.GetChild(i).gameObject.SetActive(true);
                        }
                        firstClick = false;
                    }


                    MelonLogger.Log("Clicked on custom level");
                    Level levelContainer = CustomLevelDatabase.GetLevelAtLevelIndex(__instance.levelDataIndex);

                    LevelData level = ConversionExtension.LevelDataNative(levelContainer.data);
                    MelonLogger.Log($"Loading assets for {level.songName}");
                    CustomLevelDatabase.LoadAssetsForLevel(levelContainer, level);
                    level.songSwitch = __instance.songSwitch;
                    MelonLogger.Log("Hotswapping song");
                    CustomLevelDatabase.ReplaceSong(levelContainer);

                    //Only make difficulties that actually exist for given map, available to select
                    SongDifficultyUIPanel[] difficultyUIPanels = __instance.parent.difficultyUIPanels;
                    foreach (var difficultyPanel in difficultyUIPanels)
                    {
                        //TODO determine (from a UX perspective) if it is better to just disable the difficulty button
                        difficultyPanel.isSelectable = false;
                    }

                    foreach (var availableDiff in CustomLevelDatabase.GetDifficultiesForLevel(levelContainer))
                    {
                        difficultyUIPanels[(int)availableDiff].isSelectable = true;
                    }


                    GameManager gm = GameManager.Instance;
                    Difficulty diff = gm.difficulty;

                    // We cant select by index based on difficulty
                    GameMap map = null; 
                    foreach (var m in level.maps)
                    {
                        if (m.trackData.difficulty == diff)
                        {
                            map = m;
                            MelonLogger.Log($"Found level for difficulty {System.Enum.GetName(typeof(Difficulty), diff)}");
                            break;
                        }
                    }

                    //The initial difficulty might not be available for given map, then find the first available difficulty and select that
                    if (map == null)
                    {
                        map = level.maps[0];
                        gm.difficulty = map.trackData.difficulty;
                    }

                    GameManager.SetLevel(map);


                    MelonLogger.Log("Setting song info panel");
                    SongInfoUI songInfo = __instance.parent.songInfoUI;
                    Models.AlbumArtMetadata art = levelContainer.art;
                    songInfo.songTitle.SetText(art.songName);
                    songInfo.songLength.SetText(level.songLength.ToString("0.0"));
                    songInfo.artist.SetText(art.songArtists);
                    MelonLogger.Log("Setting enemy count in info");
                    songInfo.enemyCount.SetText(map.enemyCount.ToString());
                    songInfo.tempo.SetText(art.tempo); //BPM
                    __instance.parent.lrgAlbumArt.sprite = levelContainer.sprite;

                    MelonLogger.Log("Setting koreo set");
                    //Replace the koreography in WwiseKoreographySets for the koreography to actually be used
                    foreach (var koreo in gm.levels.koreoSets)
                    {
                        foreach (var media in koreo.koreographies)
                        {
                            if (media.mediaID == 561074166) // Religion
                            {
                                //TODO Backup original koreography
                                media.koreo = level.maps[0].trackData.koreography;
                            }
                        }
                    }

                    CustomLevelDatabase.SelectedCustomLevel = true;
                    CustomLevelDatabase.CurrentSelectedLevel = level;

                    return false;
                }
                firstClick = false;
                CustomLevelDatabase.SelectedCustomLevel = false;
                return true;
            }
        }



        [HarmonyPatch(typeof(SongSelectionUIController), "SelectedEasyDifficulty", new System.Type[0])]
        public static class SongSelectionUIController_SelectedEasyDifficulty
        {
            public static bool Prefix(SongSelectionUIController __instance)
            {
                if (CustomLevelDatabase.SelectedCustomLevel)
                {
                    LevelData level = CustomLevelDatabase.CurrentSelectedLevel;
                    GameManager gm = GameManager.Instance;
                    gm.difficulty = Difficulty.Easy;
                    GameManager.SetLevel(level.maps[(int)gm.difficulty]);

                    return false;
                }


                return true;
            }
        }

        [HarmonyPatch(typeof(SongSelectionUIController), "SelectedNormalDifficulty", new System.Type[0])]
        public static class SongSelectionUIController_SelectedNormalDifficulty
        {
            public static bool Prefix(SongSelectionUIController __instance)
            {
                if (CustomLevelDatabase.SelectedCustomLevel)
                {
                    LevelData level = CustomLevelDatabase.CurrentSelectedLevel;
                    GameManager gm = GameManager.Instance;
                    gm.difficulty = Difficulty.Normal;
                    GameManager.SetLevel(level.maps[(int)gm.difficulty]);

                    return false;
                }

                return true;
            }
        }

        [HarmonyPatch(typeof(SongSelectionUIController), "SelectedHardDifficulty", new System.Type[0])]
        public static class SongSelectionUIController_SelectedHardDifficulty
        {
            public static bool Prefix(SongSelectionUIController __instance)
            {
                if (CustomLevelDatabase.SelectedCustomLevel)
                {
                    LevelData level = CustomLevelDatabase.CurrentSelectedLevel;
                    GameManager gm = GameManager.Instance;
                    gm.difficulty = Difficulty.Hard;
                    GameManager.SetLevel(level.maps[(int)gm.difficulty]);

                    return false;
                }

                return true;
            }
        }


        //[HarmonyPatch(typeof(GameplayManager), "OnGameEnd", new System.Type[0])]
        //public static class GameplayManagerMod
        //{
        //    public static void Prefix(GameplayManager __instance)
        //    {
        //        MelonLogger.Log("Pre GameplayManager.OnGameEnd");
        //    }

        //}

        [HarmonyPatch(typeof(PlayerActionManager), "OnSongComplete", new System.Type[0])]
        public static class PlayerActionManagerMod
        {
            public static void Postfix(PlayerActionManager __instance)
            {
                MelonLogger.Log("OnSongComplete postfix called");
                //if (CustomLevelDatabase.SelectedCustomLevel)
                //{
                //    CustomLevelDatabase.UnloadLoadedAssets();
                //}
            }
        }

        [HarmonyPatch(typeof(GameManager), "OnSongStop", new System.Type[0])]
        public static class GameManagerMod
        {
            public static bool Prefix(GameManager __instance)
            {
                MelonLogger.Log("GameManager.OnSongStop");
                return true;
            }
        }

        //[HarmonyPatch(typeof(PlayerActionManager), "OnSongComplete", new System.Type[0])]
        //public static class PlayerActionManagerMod
        //{
        //    public static bool Prefix(PlayerActionManager __instance)
        //    {
        //        MelonLogger.Log("PlayerActionManagerMod.OnSongComplete");
        //        return true;
        //    }

        //}

        [HarmonyPatch(typeof(PresenceManager), "OnChallengesUpdated", new System.Type[1] { typeof(ChallengeUpdateEvent)})]
        public static class PresenceManagerMod
        {
            public static bool Prefix(PresenceManager __instance)
            {
                MelonLogger.Log("PresenceManager.OnChallengesUpdated");

                return true;
            }

        }

        //Following is a work around

        /* ------!!! Thanks to MINER for figuring out the following 2 hooks !!!------- */
        //https://gitlab.com/nagytech/pistol-whip-custom-beat-loader/-/blob/master/Modification.cs
        // NOTE: there's currently an issue where sequences get enabled by the 
        // SpawnManager, but the individual enemy actions are not enabled
        // so, in some cases - the actor just stalls in one stage of the sequence.
        // HACK: For now, we force enable the actions, but will need to keep an eye 
        // out for a better solution.
        [HarmonyPatch(typeof(EnemyAction), "Enter", new System.Type[1] { typeof(float) })]
        public static class EnemyActionMod
        {
            public static void Prefix(EnemyAction __instance, float startTime)
            {
                try
                {
                    if (!__instance.enabled) __instance.enabled = true;
                    MelonLogger.Log($"{__instance.actionType}: {startTime}");
                }
                catch
                {

                }
            }
        }

        // HACK: Being over careful here with enabling sequences.  Not ideal...
        [HarmonyPatch(typeof(EnemySequence), "Play", new System.Type[1] { typeof(float) })]
        public static class EnemySequenceMod
        {
            public static void Prefix(EnemySequence __instance, float startTime)
            {
                try
                {
                    if (!__instance.enabled) __instance.enabled = true;
                }
                catch
                {

                }
            }
        }

    }
}
