#pragma once
#include "GSXProject.h"
#include "GSCPart.h"
#include "GSCScript.h"

namespace GSX_Studio {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Summary for ImportProjectDialog
	/// </summary>
	public ref class ImportProjectDialog : DevExpress::XtraEditors::XtraForm
	{
	public:
		FolderBrowserDialog^ Browser;
		System::ComponentModel::BackgroundWorker^ bgw;
		void BackgroundWorker1_DoWork(System::Object^ sender, DoWorkEventArgs^ e);
		array<System::Byte>^ BytesFromString(System::String ^ str);
		void AddProject(void);
		void AddProjectsPath(void);
		void ClearProjects(void);
		void RemoveSelectedProject(void);
		void OnTreeMouseClick(System::Object ^sender, System::Windows::Forms::MouseEventArgs ^e);
		void RefreshProjectsList(void);
		void BackgroundWorker1_RunWorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e);
		void BackgroundWorker1_ProgressChanged(System::Object^ sender, System::ComponentModel::ProgressChangedEventArgs^ e);
		Generic::List<Byte>^ GetDefaultProjectData(void);
		System::Object^ BeginImportsThread(System::Collections::Generic::List<System::String^>^ directories, System::ComponentModel::BackgroundWorker ^ bgx, System::String^ ScriptName, System::String^ Creator, bool DoReplace);
		System::Collections::Generic::List<System::String^>^ Directories = gcnew System::Collections::Generic::List<System::String^>();
		System::String^ ProjectsLocation;

		ImportProjectDialog(System::String^ plocation)
		{
			ProjectsLocation = plocation;
			InitializeComponent();
			Browser = gcnew FolderBrowserDialog();
			Browser->Description = "Select a Project";
			Browser->ShowNewFolderButton = false;
			ProjectsList->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &GSX_Studio::ImportProjectDialog::OnTreeMouseClick);
			bgw = gcnew System::ComponentModel::BackgroundWorker();
			bgw->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &GSX_Studio::ImportProjectDialog::BackgroundWorker1_DoWork);
			bgw->WorkerReportsProgress = true;
			bgw->WorkerSupportsCancellation = true;
			bgw->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &GSX_Studio::ImportProjectDialog::BackgroundWorker1_RunWorkerCompleted);
			bgw->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &GSX_Studio::ImportProjectDialog::BackgroundWorker1_ProgressChanged);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ImportProjectDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private: DevExpress::XtraEditors::LabelControl^  labelControl1;
	public: DevExpress::XtraEditors::ComboBoxEdit^  ScriptPath;
	public: DevExpress::XtraEditors::TextEdit^  CreatorName;
	private: DevExpress::XtraEditors::LabelControl^  labelControl2;
	public:
	private: DevExpress::XtraEditors::LabelControl^  labelControl3;
	private: DevExpress::XtraEditors::ComboBoxEdit^  ConflictsHandling;

	private: DevExpress::XtraTreeList::TreeList^  ProjectsList;

	private: DevExpress::XtraEditors::ProgressBarControl^  progressBarControl1;
	private: DevExpress::XtraEditors::SimpleButton^  StartImports;
	private: DevExpress::XtraEditors::SimpleButton^  AddProjects;


	private: DevExpress::XtraEditors::SimpleButton^  CancelImports;

	private: DevExpress::XtraTreeList::Columns::TreeListColumn^  treeListColumn1;
	private: DevExpress::XtraBars::BarManager^  barManager1;
	private: DevExpress::XtraBars::BarDockControl^  barDockControlTop;
	private: DevExpress::XtraBars::BarDockControl^  barDockControlBottom;
	private: DevExpress::XtraBars::BarDockControl^  barDockControlLeft;
	private: DevExpress::XtraBars::BarDockControl^  barDockControlRight;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem1;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem2;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem3;
	private: DevExpress::XtraBars::PopupMenu^  RContextMenu;
	private: DevExpress::XtraEditors::SimpleButton^  simpleButton1;

	private: System::ComponentModel::IContainer^  components;
	private:

	public:
	protected:

	protected:


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->labelControl1 = (gcnew DevExpress::XtraEditors::LabelControl());
			this->ScriptPath = (gcnew DevExpress::XtraEditors::ComboBoxEdit());
			this->CreatorName = (gcnew DevExpress::XtraEditors::TextEdit());
			this->labelControl2 = (gcnew DevExpress::XtraEditors::LabelControl());
			this->labelControl3 = (gcnew DevExpress::XtraEditors::LabelControl());
			this->ConflictsHandling = (gcnew DevExpress::XtraEditors::ComboBoxEdit());
			this->ProjectsList = (gcnew DevExpress::XtraTreeList::TreeList());
			this->treeListColumn1 = (gcnew DevExpress::XtraTreeList::Columns::TreeListColumn());
			this->progressBarControl1 = (gcnew DevExpress::XtraEditors::ProgressBarControl());
			this->StartImports = (gcnew DevExpress::XtraEditors::SimpleButton());
			this->AddProjects = (gcnew DevExpress::XtraEditors::SimpleButton());
			this->CancelImports = (gcnew DevExpress::XtraEditors::SimpleButton());
			this->barManager1 = (gcnew DevExpress::XtraBars::BarManager(this->components));
			this->barDockControlTop = (gcnew DevExpress::XtraBars::BarDockControl());
			this->barDockControlBottom = (gcnew DevExpress::XtraBars::BarDockControl());
			this->barDockControlLeft = (gcnew DevExpress::XtraBars::BarDockControl());
			this->barDockControlRight = (gcnew DevExpress::XtraBars::BarDockControl());
			this->barButtonItem1 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem2 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem3 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->RContextMenu = (gcnew DevExpress::XtraBars::PopupMenu(this->components));
			this->simpleButton1 = (gcnew DevExpress::XtraEditors::SimpleButton());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ScriptPath->Properties))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->CreatorName->Properties))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ConflictsHandling->Properties))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ProjectsList))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->progressBarControl1->Properties))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barManager1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RContextMenu))->BeginInit();
			this->SuspendLayout();
			// 
			// labelControl1
			// 
			this->labelControl1->Appearance->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelControl1->Location = System::Drawing::Point(12, 338);
			this->labelControl1->Name = L"labelControl1";
			this->labelControl1->Size = System::Drawing::Size(119, 16);
			this->labelControl1->TabIndex = 0;
			this->labelControl1->Text = L"Default Script Name:";
			// 
			// ScriptPath
			// 
			this->ScriptPath->EditValue = L"maps\\mp\\gametypes\\_clientids.gsc";
			this->ScriptPath->Location = System::Drawing::Point(180, 338);
			this->ScriptPath->Name = L"ScriptPath";
			this->ScriptPath->Properties->Buttons->AddRange(gcnew cli::array< DevExpress::XtraEditors::Controls::EditorButton^  >(1) { (gcnew DevExpress::XtraEditors::Controls::EditorButton(DevExpress::XtraEditors::Controls::ButtonPredefines::Combo)) });
			this->ScriptPath->Properties->Items->AddRange(gcnew cli::array< System::Object^  >(574) {
				L"aitype\\clientscripts\\enemy_dog_mp.csc",
					L"aitype\\enemy_dog_mp.gsc", L"character\\c_mp_german_shepherd_vest.gsc", L"character\\c_mp_german_shepherd_vest_black.gsc",
					L"character\\character_mp_german_shepherd.gsc", L"character\\clientscripts\\c_mp_german_shepherd_vest.csc", L"character\\clientscripts\\c_mp_german_shepherd_vest_black.csc",
					L"character\\clientscripts\\character_mp_german_shepherd.csc", L"clientscripts\\_radiant_live_update.csc", L"clientscripts\\_radiant_live_update.gsc",
					L"clientscripts\\mp\\_acousticsensor.csc", L"clientscripts\\mp\\_acousticsensor.gsc", L"clientscripts\\mp\\_ai_tank.csc", L"clientscripts\\mp\\_ai_tank.gsc",
					L"clientscripts\\mp\\_airsupport.csc", L"clientscripts\\mp\\_airsupport.gsc", L"clientscripts\\mp\\_ambient.csc", L"clientscripts\\mp\\_ambient.gsc",
					L"clientscripts\\mp\\_ambientpackage.csc", L"clientscripts\\mp\\_ambientpackage.gsc", L"clientscripts\\mp\\_audio.csc", L"clientscripts\\mp\\_audio.gsc",
					L"clientscripts\\mp\\_bouncingbetty.csc", L"clientscripts\\mp\\_bouncingbetty.gsc", L"clientscripts\\mp\\_burnplayer.csc", L"clientscripts\\mp\\_burnplayer.gsc",
					L"clientscripts\\mp\\_busing.csc", L"clientscripts\\mp\\_busing.gsc", L"clientscripts\\mp\\_callbacks.csc", L"clientscripts\\mp\\_callbacks.gsc",
					L"clientscripts\\mp\\_cameraspike.csc", L"clientscripts\\mp\\_cameraspike.gsc", L"clientscripts\\mp\\_claymore.csc", L"clientscripts\\mp\\_claymore.gsc",
					L"clientscripts\\mp\\_clientfaceanim_mp.csc", L"clientscripts\\mp\\_clientfaceanim_mp.gsc", L"clientscripts\\mp\\_counteruav.csc",
					L"clientscripts\\mp\\_counteruav.gsc", L"clientscripts\\mp\\_ctf.csc", L"clientscripts\\mp\\_ctf.gsc", L"clientscripts\\mp\\_decoy.csc",
					L"clientscripts\\mp\\_decoy.gsc", L"clientscripts\\mp\\_destructible.csc", L"clientscripts\\mp\\_destructible.gsc", L"clientscripts\\mp\\_dogs.csc",
					L"clientscripts\\mp\\_dogs.gsc", L"clientscripts\\mp\\_explode.csc", L"clientscripts\\mp\\_explode.gsc", L"clientscripts\\mp\\_explosive_bolt.csc",
					L"clientscripts\\mp\\_explosive_bolt.gsc", L"clientscripts\\mp\\_face_utility_mp.csc", L"clientscripts\\mp\\_face_utility_mp.gsc",
					L"clientscripts\\mp\\_filter.csc", L"clientscripts\\mp\\_filter.gsc", L"clientscripts\\mp\\_footsteps.csc", L"clientscripts\\mp\\_footsteps.gsc",
					L"clientscripts\\mp\\_fx.csc", L"clientscripts\\mp\\_fx.gsc", L"clientscripts\\mp\\_fxanim.csc", L"clientscripts\\mp\\_fxanim.gsc",
					L"clientscripts\\mp\\_global_fx.csc", L"clientscripts\\mp\\_global_fx.gsc", L"clientscripts\\mp\\_helicopter.csc", L"clientscripts\\mp\\_helicopter.gsc",
					L"clientscripts\\mp\\_helicopter_sounds.csc", L"clientscripts\\mp\\_helicopter_sounds.gsc", L"clientscripts\\mp\\_lights.csc",
					L"clientscripts\\mp\\_lights.gsc", L"clientscripts\\mp\\_load.csc", L"clientscripts\\mp\\_load.gsc", L"clientscripts\\mp\\_missile_drone.csc",
					L"clientscripts\\mp\\_missile_drone.gsc", L"clientscripts\\mp\\_missile_swarm.csc", L"clientscripts\\mp\\_missile_swarm.gsc",
					L"clientscripts\\mp\\_multi_extracam.csc", L"clientscripts\\mp\\_multi_extracam.gsc", L"clientscripts\\mp\\_music.csc", L"clientscripts\\mp\\_music.gsc",
					L"clientscripts\\mp\\_planemortar.csc", L"clientscripts\\mp\\_planemortar.gsc", L"clientscripts\\mp\\_players.csc", L"clientscripts\\mp\\_players.gsc",
					L"clientscripts\\mp\\_proximity_grenade.csc", L"clientscripts\\mp\\_proximity_grenade.gsc", L"clientscripts\\mp\\_qrdrone.csc",
					L"clientscripts\\mp\\_qrdrone.gsc", L"clientscripts\\mp\\_rcbomb.csc", L"clientscripts\\mp\\_rcbomb.gsc", L"clientscripts\\mp\\_remotemissile.csc",
					L"clientscripts\\mp\\_remotemissile.gsc", L"clientscripts\\mp\\_rewindobjects.csc", L"clientscripts\\mp\\_rewindobjects.gsc",
					L"clientscripts\\mp\\_riotshield.csc", L"clientscripts\\mp\\_riotshield.gsc", L"clientscripts\\mp\\_rotating_object.csc", L"clientscripts\\mp\\_rotating_object.gsc",
					L"clientscripts\\mp\\_satchel_charge.csc", L"clientscripts\\mp\\_satchel_charge.gsc", L"clientscripts\\mp\\_scrambler.csc", L"clientscripts\\mp\\_scrambler.gsc",
					L"clientscripts\\mp\\_sticky_grenade.csc", L"clientscripts\\mp\\_sticky_grenade.gsc", L"clientscripts\\mp\\_tacticalinsertion.csc",
					L"clientscripts\\mp\\_tacticalinsertion.gsc", L"clientscripts\\mp\\_teamset_seals.csc", L"clientscripts\\mp\\_teamset_seals.gsc",
					L"clientscripts\\mp\\_treadfx.csc", L"clientscripts\\mp\\_treadfx.gsc", L"clientscripts\\mp\\_trophy_system.csc", L"clientscripts\\mp\\_trophy_system.gsc",
					L"clientscripts\\mp\\_turret.csc", L"clientscripts\\mp\\_turret.gsc", L"clientscripts\\mp\\_utility.csc", L"clientscripts\\mp\\_utility.gsc",
					L"clientscripts\\mp\\_utility_code.csc", L"clientscripts\\mp\\_utility_code.gsc", L"clientscripts\\mp\\_vehicle.csc", L"clientscripts\\mp\\_vehicle.gsc",
					L"clientscripts\\mp\\_visionset_mgr.csc", L"clientscripts\\mp\\_visionset_mgr.gsc", L"clientscripts\\mp\\createfx\\mp_concert_fx.csc",
					L"clientscripts\\mp\\createfx\\mp_nuketown_2020_fx.csc", L"clientscripts\\mp\\gametypes\\conf.csc", L"clientscripts\\mp\\gametypes\\conf.gsc",
					L"clientscripts\\mp\\gametypes\\ctf.csc", L"clientscripts\\mp\\gametypes\\ctf.gsc", L"clientscripts\\mp\\gametypes\\dem.csc",
					L"clientscripts\\mp\\gametypes\\dem.gsc", L"clientscripts\\mp\\gametypes\\dm.csc", L"clientscripts\\mp\\gametypes\\dm.gsc", L"clientscripts\\mp\\gametypes\\dom.csc",
					L"clientscripts\\mp\\gametypes\\dom.gsc", L"clientscripts\\mp\\gametypes\\gun.csc", L"clientscripts\\mp\\gametypes\\gun.gsc",
					L"clientscripts\\mp\\gametypes\\hq.csc", L"clientscripts\\mp\\gametypes\\hq.gsc", L"clientscripts\\mp\\gametypes\\koth.csc",
					L"clientscripts\\mp\\gametypes\\koth.gsc", L"clientscripts\\mp\\gametypes\\oic.csc", L"clientscripts\\mp\\gametypes\\oic.gsc",
					L"clientscripts\\mp\\gametypes\\sas.csc", L"clientscripts\\mp\\gametypes\\sas.gsc", L"clientscripts\\mp\\gametypes\\sd.csc",
					L"clientscripts\\mp\\gametypes\\sd.gsc", L"clientscripts\\mp\\gametypes\\shrp.csc", L"clientscripts\\mp\\gametypes\\shrp.gsc",
					L"clientscripts\\mp\\gametypes\\tdm.csc", L"clientscripts\\mp\\gametypes\\tdm.gsc", L"clientscripts\\mp\\gametypes\\zclassic.csc",
					L"clientscripts\\mp\\gametypes\\zclassic.gsc", L"clientscripts\\mp\\mp_carrier.csc", L"clientscripts\\mp\\mp_carrier.gsc", L"clientscripts\\mp\\mp_dockside.csc",
					L"clientscripts\\mp\\mp_dockside.gsc", L"clientscripts\\mp\\mp_drone_fx.csc", L"clientscripts\\mp\\mp_drone_fx.gsc", L"clientscripts\\mp\\mp_express.csc",
					L"clientscripts\\mp\\mp_express.gsc", L"clientscripts\\mp\\mp_hijacked.csc", L"clientscripts\\mp\\mp_hijacked.gsc", L"clientscripts\\mp\\mp_hydro.csc",
					L"clientscripts\\mp\\mp_hydro.gsc", L"clientscripts\\mp\\mp_nuketown_2020.csc", L"clientscripts\\mp\\mp_nuketown_2020.gsc", L"clientscripts\\mp\\mp_nuketown_2020_amb.gsc",
					L"clientscripts\\mp\\mp_nuketown_2020_fx.gsc", L"clientscripts\\mp\\mp_overflow.csc", L"clientscripts\\mp\\mp_overflow.gsc",
					L"clientscripts\\mp\\mp_raid.csc", L"clientscripts\\mp\\mp_raid.gsc", L"clientscripts\\mp\\mp_uplink.csc", L"clientscripts\\mp\\mp_uplink.gsc",
					L"clientscripts\\mp\\zm_prison.gsc", L"clientscripts\\mp\\zombies\\_callbacks.csc", L"clientscripts\\mp\\zombies\\_callbacks.gsc",
					L"clientscripts\\mp\\zombies\\_clientfaceanim_zm.csc", L"clientscripts\\mp\\zombies\\_clientfaceanim_zm.gsc", L"clientscripts\\mp\\zombies\\_face_utility_zm.csc",
					L"clientscripts\\mp\\zombies\\_face_utility_zm.gsc", L"clientscripts\\mp\\zombies\\_load.csc", L"clientscripts\\mp\\zombies\\_load.gsc",
					L"clientscripts\\mp\\zombies\\_players.csc", L"clientscripts\\mp\\zombies\\_players.gsc", L"clientscripts\\mp\\zombies\\_zm.csc",
					L"clientscripts\\mp\\zombies\\_zm.gsc", L"clientscripts\\mp\\zombies\\_zm_audio.csc", L"clientscripts\\mp\\zombies\\_zm_audio.gsc",
					L"clientscripts\\mp\\zombies\\_zm_buildables.csc", L"clientscripts\\mp\\zombies\\_zm_buildables.gsc", L"clientscripts\\mp\\zombies\\_zm_clone.csc",
					L"clientscripts\\mp\\zombies\\_zm_clone.gsc", L"clientscripts\\mp\\zombies\\_zm_equip_gasmask.csc", L"clientscripts\\mp\\zombies\\_zm_equip_gasmask.gsc",
					L"clientscripts\\mp\\zombies\\_zm_equip_hacker.csc", L"clientscripts\\mp\\zombies\\_zm_equip_hacker.gsc", L"clientscripts\\mp\\zombies\\_zm_equipment.csc",
					L"clientscripts\\mp\\zombies\\_zm_equipment.gsc", L"clientscripts\\mp\\zombies\\_zm_ffotd.csc", L"clientscripts\\mp\\zombies\\_zm_ffotd.gsc",
					L"clientscripts\\mp\\zombies\\_zm_gump.csc", L"clientscripts\\mp\\zombies\\_zm_gump.gsc", L"clientscripts\\mp\\zombies\\_zm_magicbox.csc",
					L"clientscripts\\mp\\zombies\\_zm_magicbox.gsc", L"clientscripts\\mp\\zombies\\_zm_perks.csc", L"clientscripts\\mp\\zombies\\_zm_perks.gsc",
					L"clientscripts\\mp\\zombies\\_zm_powerups.csc", L"clientscripts\\mp\\zombies\\_zm_powerups.gsc", L"clientscripts\\mp\\zombies\\_zm_score.csc",
					L"clientscripts\\mp\\zombies\\_zm_score.gsc", L"clientscripts\\mp\\zombies\\_zm_traps.csc", L"clientscripts\\mp\\zombies\\_zm_traps.gsc",
					L"clientscripts\\mp\\zombies\\_zm_utility.csc", L"clientscripts\\mp\\zombies\\_zm_utility.gsc", L"clientscripts\\mp\\zombies\\_zm_weap_cymbal_monkey.csc",
					L"clientscripts\\mp\\zombies\\_zm_weap_cymbal_monkey.gsc", L"clientscripts\\mp\\zombies\\_zm_weap_thundergun.csc", L"clientscripts\\mp\\zombies\\_zm_weap_thundergun.gsc",
					L"clientscripts\\mp\\zombies\\_zm_weapons.csc", L"clientscripts\\mp\\zombies\\_zm_weapons.gsc", L"codescripts\\character.gsc",
					L"codescripts\\character_mp.gsc", L"codescripts\\delete.csc", L"codescripts\\delete.gsc", L"codescripts\\struct.csc", L"codescripts\\struct.gsc",
					L"common_scripts\\utility.gsc", L"maps\\mp\\_acousticsensor.gsc", L"maps\\mp\\_ambientpackage.gsc", L"maps\\mp\\_art.gsc", L"maps\\mp\\_audio.gsc",
					L"maps\\mp\\_ballistic_knife.gsc", L"maps\\mp\\_bb.gsc", L"maps\\mp\\_bouncingbetty.gsc", L"maps\\mp\\_burnplayer.gsc", L"maps\\mp\\_busing.gsc",
					L"maps\\mp\\_challenges.gsc", L"maps\\mp\\_compass.gsc", L"maps\\mp\\_createfx.gsc", L"maps\\mp\\_createfxmenu.gsc", L"maps\\mp\\_createfxundo.gsc",
					L"maps\\mp\\_decoy.gsc", L"maps\\mp\\_demo.gsc", L"maps\\mp\\_destructible.gsc", L"maps\\mp\\_development_dvars.gsc", L"maps\\mp\\_empgrenade.gsc",
					L"maps\\mp\\_entityheadicons.gsc", L"maps\\mp\\_events.gsc", L"maps\\mp\\_explosive_bolt.gsc", L"maps\\mp\\_flashgrenades.gsc",
					L"maps\\mp\\_fx.gsc", L"maps\\mp\\_fxanim.gsc", L"maps\\mp\\_gameadvertisement.gsc", L"maps\\mp\\_gamerep.gsc", L"maps\\mp\\_global_fx.gsc",
					L"maps\\mp\\_hacker_tool.gsc", L"maps\\mp\\_heatseekingmissile.gsc", L"maps\\mp\\_interactive_objects.gsc", L"maps\\mp\\_load.gsc",
					L"maps\\mp\\_medals.gsc", L"maps\\mp\\_menus.gsc", L"maps\\mp\\_mgturret.gsc", L"maps\\mp\\_multi_extracam.gsc", L"maps\\mp\\_music.gsc",
					L"maps\\mp\\_pc.gsc", L"maps\\mp\\_popups.gsc", L"maps\\mp\\_proximity_grenade.gsc", L"maps\\mp\\_riotshield.gsc", L"maps\\mp\\_satchel_charge.gsc",
					L"maps\\mp\\_scoreevents.gsc", L"maps\\mp\\_scoreevents.gsct", L"maps\\mp\\_scrambler.gsc", L"maps\\mp\\_script_gen.gsc", L"maps\\mp\\_sensor_grenade.gsc",
					L"maps\\mp\\_serverfaceanim_mp.gsc", L"maps\\mp\\_smokegrenade.gsc", L"maps\\mp\\_sticky_grenade.gsc", L"maps\\mp\\_tabun.gsc",
					L"maps\\mp\\_tacticalinsertion.gsc", L"maps\\mp\\_teargrenades.gsc", L"maps\\mp\\_treadfx.gsc", L"maps\\mp\\_trophy_system.gsc",
					L"maps\\mp\\_utility.gsc", L"maps\\mp\\_vehicles.gsc", L"maps\\mp\\_visionset_mgr.gsc", L"maps\\mp\\animscripts\\dog_combat.gsc",
					L"maps\\mp\\animscripts\\dog_death.gsc", L"maps\\mp\\animscripts\\dog_flashed.gsc", L"maps\\mp\\animscripts\\dog_init.gsc", L"maps\\mp\\animscripts\\dog_jump.gsc",
					L"maps\\mp\\animscripts\\dog_move.gsc", L"maps\\mp\\animscripts\\dog_pain.gsc", L"maps\\mp\\animscripts\\dog_stop.gsc", L"maps\\mp\\animscripts\\dog_turn.gsc",
					L"maps\\mp\\animscripts\\shared.gsc", L"maps\\mp\\animscripts\\traverse\\jump_down_40.gsc", L"maps\\mp\\animscripts\\traverse\\jump_down_56.gsc",
					L"maps\\mp\\animscripts\\traverse\\jump_down_96.gsc", L"maps\\mp\\animscripts\\traverse\\mantle_on_40.gsc", L"maps\\mp\\animscripts\\traverse\\mantle_on_56.gsc",
					L"maps\\mp\\animscripts\\traverse\\mantle_on_80.gsc", L"maps\\mp\\animscripts\\traverse\\mantle_on_96.gsc", L"maps\\mp\\animscripts\\traverse\\mantle_over_40.gsc",
					L"maps\\mp\\animscripts\\traverse\\mantle_window_36.gsc", L"maps\\mp\\animscripts\\traverse\\shared.gsc", L"maps\\mp\\animscripts\\traverse\\through_hole_42.gsc",
					L"maps\\mp\\animscripts\\traverse\\zm_mantle_over_40.gsc", L"maps\\mp\\animscripts\\traverse\\zm_shared.gsc", L"maps\\mp\\animscripts\\utility.gsc",
					L"maps\\mp\\animscripts\\zm_combat.gsc", L"maps\\mp\\animscripts\\zm_death.gsc", L"maps\\mp\\animscripts\\zm_dog_combat.gsc",
					L"maps\\mp\\animscripts\\zm_dog_death.gsc", L"maps\\mp\\animscripts\\zm_dog_flashed.gsc", L"maps\\mp\\animscripts\\zm_dog_init.gsc",
					L"maps\\mp\\animscripts\\zm_dog_jump.gsc", L"maps\\mp\\animscripts\\zm_dog_move.gsc", L"maps\\mp\\animscripts\\zm_dog_pain.gsc",
					L"maps\\mp\\animscripts\\zm_dog_stop.gsc", L"maps\\mp\\animscripts\\zm_dog_turn.gsc", L"maps\\mp\\animscripts\\zm_flashed.gsc",
					L"maps\\mp\\animscripts\\zm_init.gsc", L"maps\\mp\\animscripts\\zm_jump.gsc", L"maps\\mp\\animscripts\\zm_melee.gsc", L"maps\\mp\\animscripts\\zm_move.gsc",
					L"maps\\mp\\animscripts\\zm_pain.gsc", L"maps\\mp\\animscripts\\zm_run.gsc", L"maps\\mp\\animscripts\\zm_scripted.gsc", L"maps\\mp\\animscripts\\zm_shared.gsc",
					L"maps\\mp\\animscripts\\zm_stop.gsc", L"maps\\mp\\animscripts\\zm_turn.gsc", L"maps\\mp\\animscripts\\zm_utility.gsc", L"maps\\mp\\bots\\_bot.gsc",
					L"maps\\mp\\bots\\_bot_combat.gsc", L"maps\\mp\\bots\\_bot_conf.gsc", L"maps\\mp\\bots\\_bot_ctf.gsc", L"maps\\mp\\bots\\_bot_dem.gsc",
					L"maps\\mp\\bots\\_bot_dom.gsc", L"maps\\mp\\bots\\_bot_hack.gsc", L"maps\\mp\\bots\\_bot_hq.gsc", L"maps\\mp\\bots\\_bot_koth.gsc",
					L"maps\\mp\\bots\\_bot_loadout.gsc", L"maps\\mp\\bots\\_bot_sd.gsc", L"maps\\mp\\createart\\mp_nuketown_2020_art.gsc", L"maps\\mp\\createfx\\mp_nuketown_2020_fx.gsc",
					L"maps\\mp\\gametypes\\_battlechatter_mp.gsc", L"maps\\mp\\gametypes\\_callbacksetup.gsc", L"maps\\mp\\gametypes\\_class.gsc",
					L"maps\\mp\\gametypes\\_clientids.gsc", L"maps\\mp\\gametypes\\_copter.gsc", L"maps\\mp\\gametypes\\_damagefeedback.gsc", L"maps\\mp\\gametypes\\_deathicons.gsc",
					L"maps\\mp\\gametypes\\_dev.gsc", L"maps\\mp\\gametypes\\_dev_class.gsc", L"maps\\mp\\gametypes\\_friendicons.gsc", L"maps\\mp\\gametypes\\_gameobjects.gsc",
					L"maps\\mp\\gametypes\\_globalentities.gsc", L"maps\\mp\\gametypes\\_globallogic.gsc", L"maps\\mp\\gametypes\\_globallogic_actor.gsc",
					L"maps\\mp\\gametypes\\_globallogic_audio.gsc", L"maps\\mp\\gametypes\\_globallogic_defaults.gsc", L"maps\\mp\\gametypes\\_globallogic_player.gsc",
					L"maps\\mp\\gametypes\\_globallogic_score.gsc", L"maps\\mp\\gametypes\\_globallogic_spawn.gsc", L"maps\\mp\\gametypes\\_globallogic_ui.gsc",
					L"maps\\mp\\gametypes\\_globallogic_utils.gsc", L"maps\\mp\\gametypes\\_globallogic_vehicle.gsc", L"maps\\mp\\gametypes\\_healthoverlay.gsc",
					L"maps\\mp\\gametypes\\_hostmigration.gsc", L"maps\\mp\\gametypes\\_hud.gsc", L"maps\\mp\\gametypes\\_hud_message.gsc", L"maps\\mp\\gametypes\\_hud_util.gsc",
					L"maps\\mp\\gametypes\\_killcam.gsc", L"maps\\mp\\gametypes\\_menus.gsc", L"maps\\mp\\gametypes\\_objpoints.gsc", L"maps\\mp\\gametypes\\_perplayer.gsc",
					L"maps\\mp\\gametypes\\_persistence.gsc", L"maps\\mp\\gametypes\\_pregame.gsc", L"maps\\mp\\gametypes\\_rank.gsc", L"maps\\mp\\gametypes\\_scoreboard.gsc",
					L"maps\\mp\\gametypes\\_serversettings.gsc", L"maps\\mp\\gametypes\\_shellshock.gsc", L"maps\\mp\\gametypes\\_spawning.gsc",
					L"maps\\mp\\gametypes\\_spawnlogic.gsc", L"maps\\mp\\gametypes\\_spectating.gsc", L"maps\\mp\\gametypes\\_tweakables.gsc", L"maps\\mp\\gametypes\\_wager.gsc",
					L"maps\\mp\\gametypes\\_weapon_utils.gsc", L"maps\\mp\\gametypes\\_weaponobjects.gsc", L"maps\\mp\\gametypes\\_weapons.gsc",
					L"maps\\mp\\gametypes\\conf.gsc", L"maps\\mp\\gametypes\\ctf.gsc", L"maps\\mp\\gametypes\\dem.gsc", L"maps\\mp\\gametypes\\dm.gsc",
					L"maps\\mp\\gametypes\\dom.gsc", L"maps\\mp\\gametypes\\gun.gsc", L"maps\\mp\\gametypes\\hq.gsc", L"maps\\mp\\gametypes\\koth.gsc",
					L"maps\\mp\\gametypes\\oic.gsc", L"maps\\mp\\gametypes\\oneflag.gsc", L"maps\\mp\\gametypes\\sas.gsc", L"maps\\mp\\gametypes\\sd.gsc",
					L"maps\\mp\\gametypes\\shrp.gsc", L"maps\\mp\\gametypes\\tdm.gsc", L"maps\\mp\\gametypes_zm\\_callbacksetup.gsc", L"maps\\mp\\gametypes_zm\\_clientids.gsc",
					L"maps\\mp\\gametypes_zm\\_damagefeedback.gsc", L"maps\\mp\\gametypes_zm\\_dev.gsc", L"maps\\mp\\gametypes_zm\\_gameobjects.gsc",
					L"maps\\mp\\gametypes_zm\\_globalentities.gsc", L"maps\\mp\\gametypes_zm\\_globallogic.gsc", L"maps\\mp\\gametypes_zm\\_globallogic_actor.gsc",
					L"maps\\mp\\gametypes_zm\\_globallogic_audio.gsc", L"maps\\mp\\gametypes_zm\\_globallogic_defaults.gsc", L"maps\\mp\\gametypes_zm\\_globallogic_player.gsc",
					L"maps\\mp\\gametypes_zm\\_globallogic_score.gsc", L"maps\\mp\\gametypes_zm\\_globallogic_spawn.gsc", L"maps\\mp\\gametypes_zm\\_globallogic_ui.gsc",
					L"maps\\mp\\gametypes_zm\\_globallogic_utils.gsc", L"maps\\mp\\gametypes_zm\\_globallogic_vehicle.gsc", L"maps\\mp\\gametypes_zm\\_gv_actions.gsc",
					L"maps\\mp\\gametypes_zm\\_healthoverlay.gsc", L"maps\\mp\\gametypes_zm\\_hostmigration.gsc", L"maps\\mp\\gametypes_zm\\_hud.gsc",
					L"maps\\mp\\gametypes_zm\\_hud_message.gsc", L"maps\\mp\\gametypes_zm\\_hud_util.gsc", L"maps\\mp\\gametypes_zm\\_menus.gsc",
					L"maps\\mp\\gametypes_zm\\_perplayer.gsc", L"maps\\mp\\gametypes_zm\\_scoreboard.gsc", L"maps\\mp\\gametypes_zm\\_serversettings.gsc",
					L"maps\\mp\\gametypes_zm\\_shellshock.gsc", L"maps\\mp\\gametypes_zm\\_spawning.gsc", L"maps\\mp\\gametypes_zm\\_spawnlogic.gsc",
					L"maps\\mp\\gametypes_zm\\_spectating.gsc", L"maps\\mp\\gametypes_zm\\_tweakables.gsc", L"maps\\mp\\gametypes_zm\\_weapon_utils.gsc",
					L"maps\\mp\\gametypes_zm\\_weaponobjects.gsc", L"maps\\mp\\gametypes_zm\\_weapons.gsc", L"maps\\mp\\gametypes_zm\\_zm_gametype.gsc",
					L"maps\\mp\\gametypes_zm\\zclassic.gsc", L"maps\\mp\\killstreaks\\_ai_tank.gsc", L"maps\\mp\\killstreaks\\_airsupport.gsc", L"maps\\mp\\killstreaks\\_dogs.gsc",
					L"maps\\mp\\killstreaks\\_emp.gsc", L"maps\\mp\\killstreaks\\_helicopter.gsc", L"maps\\mp\\killstreaks\\_helicopter_guard.gsc",
					L"maps\\mp\\killstreaks\\_helicopter_gunner.gsc", L"maps\\mp\\killstreaks\\_killstreak_weapons.gsc", L"maps\\mp\\killstreaks\\_killstreakrules.gsc",
					L"maps\\mp\\killstreaks\\_killstreaks.gsc", L"maps\\mp\\killstreaks\\_missile_drone.gsc", L"maps\\mp\\killstreaks\\_missile_swarm.gsc",
					L"maps\\mp\\killstreaks\\_planemortar.gsc", L"maps\\mp\\killstreaks\\_qrdrone.gsc", L"maps\\mp\\killstreaks\\_radar.gsc", L"maps\\mp\\killstreaks\\_rcbomb.gsc",
					L"maps\\mp\\killstreaks\\_remote_weapons.gsc", L"maps\\mp\\killstreaks\\_remotemissile.gsc", L"maps\\mp\\killstreaks\\_remotemortar.gsc",
					L"maps\\mp\\killstreaks\\_spyplane.gsc", L"maps\\mp\\killstreaks\\_straferun.gsc", L"maps\\mp\\killstreaks\\_supplycrate.gsc",
					L"maps\\mp\\killstreaks\\_supplydrop.gsc", L"maps\\mp\\killstreaks\\_turret_killstreak.gsc", L"maps\\mp\\mp_bridge.gsc", L"maps\\mp\\mp_carrier.gsc",
					L"maps\\mp\\mp_castaway.gsc", L"maps\\mp\\mp_concert.gsc", L"maps\\mp\\mp_dig.gsc", L"maps\\mp\\mp_dockside.gsc", L"maps\\mp\\mp_dockside_crane.gsc",
					L"maps\\mp\\mp_downhill.gsc", L"maps\\mp\\mp_downhill_cablecar.gsc", L"maps\\mp\\mp_drone.gsc", L"maps\\mp\\mp_express.gsc",
					L"maps\\mp\\mp_express_train.gsc", L"maps\\mp\\mp_frostbite.gsc", L"maps\\mp\\mp_hijacked.gsc", L"maps\\mp\\mp_hydro.gsc", L"maps\\mp\\mp_la.gsc",
					L"maps\\mp\\mp_magma.gsc", L"maps\\mp\\mp_meltdown.gsc", L"maps\\mp\\mp_mirage.gsc", L"maps\\mp\\mp_nightclub.gsc", L"maps\\mp\\mp_nuketown_2020.gsc",
					L"maps\\mp\\mp_nuketown_2020_amb.gsc", L"maps\\mp\\mp_nuketown_2020_fx.gsc", L"maps\\mp\\mp_overflow.gsc", L"maps\\mp\\mp_paintball.gsc",
					L"maps\\mp\\mp_pod.gsc", L"maps\\mp\\mp_raid.gsc", L"maps\\mp\\mp_skate.gsc", L"maps\\mp\\mp_slums.gsc", L"maps\\mp\\mp_socotra.gsc",
					L"maps\\mp\\mp_studio.gsc", L"maps\\mp\\mp_takeoff.gsc", L"maps\\mp\\mp_turbine.gsc", L"maps\\mp\\mp_uplink.gsc", L"maps\\mp\\mp_vertigo.gsc",
					L"maps\\mp\\mp_village.gsc", L"maps\\mp\\teams\\_teams.gsc", L"maps\\mp\\teams\\_teamset.gsc", L"maps\\mp\\teams\\_teamset_multiteam.gsc",
					L"maps\\mp\\teams\\_teamset_pmc.gsc", L"maps\\mp\\teams\\_teamset_seals.gsc", L"maps\\mp\\zm_tomb_craftables.gsc", L"maps\\mp\\zm_tomb_distance_tracking.gsc",
					L"maps\\mp\\zm_tomb_ffotd.gsc", L"maps\\mp\\zm_tomb_tank.gsc", L"maps\\mp\\zombies\\_load.gsc", L"maps\\mp\\zombies\\_zm.gsc",
					L"maps\\mp\\zombies\\_zm_ai_basic.gsc", L"maps\\mp\\zombies\\_zm_ai_dogs.gsc", L"maps\\mp\\zombies\\_zm_ai_faller.gsc", L"maps\\mp\\zombies\\_zm_ai_mechz_ffotd.gsc",
					L"maps\\mp\\zombies\\_zm_audio.gsc", L"maps\\mp\\zombies\\_zm_audio_announcer.gsc", L"maps\\mp\\zombies\\_zm_blockers.gsc", L"maps\\mp\\zombies\\_zm_bot.gsc",
					L"maps\\mp\\zombies\\_zm_buildables.gsc", L"maps\\mp\\zombies\\_zm_chugabud.gsc", L"maps\\mp\\zombies\\_zm_clone.gsc", L"maps\\mp\\zombies\\_zm_devgui.gsc",
					L"maps\\mp\\zombies\\_zm_equip_gasmask.gsc", L"maps\\mp\\zombies\\_zm_equip_hacker.gsc", L"maps\\mp\\zombies\\_zm_equip_turbine.gsc",
					L"maps\\mp\\zombies\\_zm_equipment.gsc", L"maps\\mp\\zombies\\_zm_ffotd.gsc", L"maps\\mp\\zombies\\_zm_game_module.gsc", L"maps\\mp\\zombies\\_zm_gump.gsc",
					L"maps\\mp\\zombies\\_zm_hackables_boards.gsc", L"maps\\mp\\zombies\\_zm_hackables_box.gsc", L"maps\\mp\\zombies\\_zm_hackables_doors.gsc",
					L"maps\\mp\\zombies\\_zm_hackables_packapunch.gsc", L"maps\\mp\\zombies\\_zm_hackables_perks.gsc", L"maps\\mp\\zombies\\_zm_hackables_powerups.gsc",
					L"maps\\mp\\zombies\\_zm_hackables_wallbuys.gsc", L"maps\\mp\\zombies\\_zm_jump_pad.gsc", L"maps\\mp\\zombies\\_zm_laststand.gsc",
					L"maps\\mp\\zombies\\_zm_magicbox.gsc", L"maps\\mp\\zombies\\_zm_magicbox_lock.gsc", L"maps\\mp\\zombies\\_zm_mgturret.gsc",
					L"maps\\mp\\zombies\\_zm_net.gsc", L"maps\\mp\\zombies\\_zm_perk_electric_cherry.gsc", L"maps\\mp\\zombies\\_zm_perks.gsc", L"maps\\mp\\zombies\\_zm_pers_upgrades.gsc",
					L"maps\\mp\\zombies\\_zm_pers_upgrades_functions.gsc", L"maps\\mp\\zombies\\_zm_pers_upgrades_system.gsc", L"maps\\mp\\zombies\\_zm_playerhealth.gsc",
					L"maps\\mp\\zombies\\_zm_power.gsc", L"maps\\mp\\zombies\\_zm_powerups.gsc", L"maps\\mp\\zombies\\_zm_score.gsc", L"maps\\mp\\zombies\\_zm_server_throttle.gsc",
					L"maps\\mp\\zombies\\_zm_sidequests.gsc", L"maps\\mp\\zombies\\_zm_spawner.gsc", L"maps\\mp\\zombies\\_zm_stats.gsc", L"maps\\mp\\zombies\\_zm_timer.gsc",
					L"maps\\mp\\zombies\\_zm_tombstone.gsc", L"maps\\mp\\zombies\\_zm_traps.gsc", L"maps\\mp\\zombies\\_zm_turned.gsc", L"maps\\mp\\zombies\\_zm_unitrigger.gsc",
					L"maps\\mp\\zombies\\_zm_utility.gsc", L"maps\\mp\\zombies\\_zm_weap_cymbal_monkey.gsc", L"maps\\mp\\zombies\\_zm_weap_thundergun.gsc",
					L"maps\\mp\\zombies\\_zm_weapons.gsc", L"maps\\mp\\zombies\\_zm_zonemgr.gsc", L"mpbody\\class_assault_rus_pmc.gsc", L"mpbody\\class_assault_usa_seals.gsc",
					L"mpbody\\class_lmg_rus_pmc.gsc", L"mpbody\\class_lmg_usa_seals.gsc", L"mpbody\\class_shotgun_rus_pmc.gsc", L"mpbody\\class_shotgun_usa_seals.gsc",
					L"mpbody\\class_smg_rus_pmc.gsc", L"mpbody\\class_smg_usa_seals.gsc", L"mpbody\\class_sniper_usa_seals.gsc"
			});
			this->ScriptPath->Properties->Sorted = true;
			this->ScriptPath->Properties->TextEditStyle = DevExpress::XtraEditors::Controls::TextEditStyles::DisableTextEditor;
			this->ScriptPath->Size = System::Drawing::Size(277, 20);
			this->ScriptPath->TabIndex = 6;
			// 
			// CreatorName
			// 
			this->CreatorName->Location = System::Drawing::Point(180, 364);
			this->CreatorName->Name = L"CreatorName";
			this->CreatorName->Size = System::Drawing::Size(277, 20);
			this->CreatorName->TabIndex = 7;
			// 
			// labelControl2
			// 
			this->labelControl2->Appearance->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelControl2->Location = System::Drawing::Point(12, 365);
			this->labelControl2->Name = L"labelControl2";
			this->labelControl2->Size = System::Drawing::Size(85, 16);
			this->labelControl2->TabIndex = 8;
			this->labelControl2->Text = L"Creator Name:";
			// 
			// labelControl3
			// 
			this->labelControl3->Appearance->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelControl3->Location = System::Drawing::Point(12, 391);
			this->labelControl3->Name = L"labelControl3";
			this->labelControl3->Size = System::Drawing::Size(100, 16);
			this->labelControl3->TabIndex = 10;
			this->labelControl3->Text = L"Naming Conflicts:";
			// 
			// ConflictsHandling
			// 
			this->ConflictsHandling->EditValue = L"Overwrite Existing GSX Projects";
			this->ConflictsHandling->Location = System::Drawing::Point(180, 390);
			this->ConflictsHandling->Name = L"ConflictsHandling";
			this->ConflictsHandling->Properties->Buttons->AddRange(gcnew cli::array< DevExpress::XtraEditors::Controls::EditorButton^  >(1) { (gcnew DevExpress::XtraEditors::Controls::EditorButton(DevExpress::XtraEditors::Controls::ButtonPredefines::Combo)) });
			this->ConflictsHandling->Properties->Items->AddRange(gcnew cli::array< System::Object^  >(2) {
				L"Overwrite Existing GSX Projects",
					L"Ignore Projects with Same Name"
			});
			this->ConflictsHandling->Properties->TextEditStyle = DevExpress::XtraEditors::Controls::TextEditStyles::DisableTextEditor;
			this->ConflictsHandling->Size = System::Drawing::Size(277, 20);
			this->ConflictsHandling->TabIndex = 11;
			// 
			// ProjectsList
			// 
			this->ProjectsList->Columns->AddRange(gcnew cli::array< DevExpress::XtraTreeList::Columns::TreeListColumn^  >(1) { this->treeListColumn1 });
			this->ProjectsList->Location = System::Drawing::Point(12, 12);
			this->ProjectsList->Name = L"ProjectsList";
			this->ProjectsList->OptionsBehavior->Editable = false;
			this->ProjectsList->OptionsBehavior->ImmediateEditor = false;
			this->ProjectsList->OptionsBehavior->KeepSelectedOnClick = false;
			this->ProjectsList->OptionsCustomization->AllowBandMoving = false;
			this->ProjectsList->OptionsCustomization->AllowColumnMoving = false;
			this->ProjectsList->OptionsCustomization->AllowQuickHideColumns = false;
			this->ProjectsList->OptionsCustomization->ShowBandsInCustomizationForm = false;
			this->ProjectsList->OptionsLayout->AddNewColumns = false;
			this->ProjectsList->OptionsMenu->EnableColumnMenu = false;
			this->ProjectsList->OptionsMenu->EnableFooterMenu = false;
			this->ProjectsList->OptionsMenu->ShowAutoFilterRowItem = false;
			this->ProjectsList->OptionsSelection->SelectNodesOnRightClick = true;
			this->ProjectsList->Size = System::Drawing::Size(719, 320);
			this->ProjectsList->TabIndex = 12;
			// 
			// treeListColumn1
			// 
			this->treeListColumn1->Caption = L"Project Name";
			this->treeListColumn1->FieldName = L"Project Name";
			this->treeListColumn1->MinWidth = 34;
			this->treeListColumn1->Name = L"treeListColumn1";
			this->treeListColumn1->Visible = true;
			this->treeListColumn1->VisibleIndex = 0;
			// 
			// progressBarControl1
			// 
			this->progressBarControl1->Location = System::Drawing::Point(12, 425);
			this->progressBarControl1->Name = L"progressBarControl1";
			this->progressBarControl1->Properties->LookAndFeel->SkinName = L"Visual Studio 2013 Dark";
			this->progressBarControl1->Properties->LookAndFeel->UseDefaultLookAndFeel = false;
			this->progressBarControl1->Properties->Step = 1;
			this->progressBarControl1->ShowProgressInTaskBar = true;
			this->progressBarControl1->Size = System::Drawing::Size(719, 18);
			this->progressBarControl1->TabIndex = 13;
			// 
			// StartImports
			// 
			this->StartImports->Enabled = false;
			this->StartImports->Location = System::Drawing::Point(463, 381);
			this->StartImports->Name = L"StartImports";
			this->StartImports->Size = System::Drawing::Size(131, 38);
			this->StartImports->TabIndex = 14;
			this->StartImports->Text = L"Start Import";
			this->StartImports->Click += gcnew System::EventHandler(this, &ImportProjectDialog::StartImports_Click);
			// 
			// AddProjects
			// 
			this->AddProjects->Location = System::Drawing::Point(600, 337);
			this->AddProjects->Name = L"AddProjects";
			this->AddProjects->Size = System::Drawing::Size(131, 38);
			this->AddProjects->TabIndex = 15;
			this->AddProjects->Text = L"Add Projects Folder";
			this->AddProjects->Click += gcnew System::EventHandler(this, &ImportProjectDialog::AddProjects_Click);
			// 
			// CancelImports
			// 
			this->CancelImports->Enabled = false;
			this->CancelImports->Location = System::Drawing::Point(600, 381);
			this->CancelImports->Name = L"CancelImports";
			this->CancelImports->Size = System::Drawing::Size(131, 38);
			this->CancelImports->TabIndex = 16;
			this->CancelImports->Text = L"Cancel";
			this->CancelImports->Visible = false;
			this->CancelImports->Click += gcnew System::EventHandler(this, &ImportProjectDialog::CancelImports_Click);
			// 
			// barManager1
			// 
			this->barManager1->DockControls->Add(this->barDockControlTop);
			this->barManager1->DockControls->Add(this->barDockControlBottom);
			this->barManager1->DockControls->Add(this->barDockControlLeft);
			this->barManager1->DockControls->Add(this->barDockControlRight);
			this->barManager1->Form = this;
			this->barManager1->Items->AddRange(gcnew cli::array< DevExpress::XtraBars::BarItem^  >(3) {
				this->barButtonItem1, this->barButtonItem2,
					this->barButtonItem3
			});
			this->barManager1->MaxItemId = 3;
			// 
			// barDockControlTop
			// 
			this->barDockControlTop->CausesValidation = false;
			this->barDockControlTop->Dock = System::Windows::Forms::DockStyle::Top;
			this->barDockControlTop->Location = System::Drawing::Point(0, 0);
			this->barDockControlTop->Size = System::Drawing::Size(748, 0);
			// 
			// barDockControlBottom
			// 
			this->barDockControlBottom->CausesValidation = false;
			this->barDockControlBottom->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->barDockControlBottom->Location = System::Drawing::Point(0, 454);
			this->barDockControlBottom->Size = System::Drawing::Size(748, 0);
			// 
			// barDockControlLeft
			// 
			this->barDockControlLeft->CausesValidation = false;
			this->barDockControlLeft->Dock = System::Windows::Forms::DockStyle::Left;
			this->barDockControlLeft->Location = System::Drawing::Point(0, 0);
			this->barDockControlLeft->Size = System::Drawing::Size(0, 454);
			// 
			// barDockControlRight
			// 
			this->barDockControlRight->CausesValidation = false;
			this->barDockControlRight->Dock = System::Windows::Forms::DockStyle::Right;
			this->barDockControlRight->Location = System::Drawing::Point(748, 0);
			this->barDockControlRight->Size = System::Drawing::Size(0, 454);
			// 
			// barButtonItem1
			// 
			this->barButtonItem1->Caption = L"Remove Selected";
			this->barButtonItem1->Id = 0;
			this->barButtonItem1->Name = L"barButtonItem1";
			this->barButtonItem1->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &ImportProjectDialog::barButtonItem1_ItemClick);
			// 
			// barButtonItem2
			// 
			this->barButtonItem2->Caption = L"Clear All";
			this->barButtonItem2->Id = 1;
			this->barButtonItem2->Name = L"barButtonItem2";
			this->barButtonItem2->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &ImportProjectDialog::barButtonItem2_ItemClick);
			// 
			// barButtonItem3
			// 
			this->barButtonItem3->Caption = L"Add Projects";
			this->barButtonItem3->Id = 2;
			this->barButtonItem3->Name = L"barButtonItem3";
			// 
			// RContextMenu
			// 
			this->RContextMenu->LinksPersistInfo->AddRange(gcnew cli::array< DevExpress::XtraBars::LinkPersistInfo^  >(2) {
				(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem1)),
					(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem2))
			});
			this->RContextMenu->Manager = this->barManager1;
			this->RContextMenu->Name = L"RContextMenu";
			// 
			// simpleButton1
			// 
			this->simpleButton1->Location = System::Drawing::Point(463, 338);
			this->simpleButton1->Name = L"simpleButton1";
			this->simpleButton1->Size = System::Drawing::Size(131, 37);
			this->simpleButton1->TabIndex = 26;
			this->simpleButton1->Text = L"Add Project";
			this->simpleButton1->Click += gcnew System::EventHandler(this, &ImportProjectDialog::simpleButton1_Click);
			// 
			// ImportProjectDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(748, 454);
			this->Controls->Add(this->simpleButton1);
			this->Controls->Add(this->CancelImports);
			this->Controls->Add(this->AddProjects);
			this->Controls->Add(this->StartImports);
			this->Controls->Add(this->progressBarControl1);
			this->Controls->Add(this->ProjectsList);
			this->Controls->Add(this->ConflictsHandling);
			this->Controls->Add(this->labelControl3);
			this->Controls->Add(this->labelControl2);
			this->Controls->Add(this->CreatorName);
			this->Controls->Add(this->ScriptPath);
			this->Controls->Add(this->labelControl1);
			this->Controls->Add(this->barDockControlLeft);
			this->Controls->Add(this->barDockControlRight);
			this->Controls->Add(this->barDockControlBottom);
			this->Controls->Add(this->barDockControlTop);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->LookAndFeel->SkinName = L"Visual Studio 2013 Dark";
			this->LookAndFeel->UseDefaultLookAndFeel = false;
			this->Name = L"ImportProjectDialog";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Import Project";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ScriptPath->Properties))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->CreatorName->Properties))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ConflictsHandling->Properties))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ProjectsList))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->progressBarControl1->Properties))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barManager1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RContextMenu))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void simpleButton1_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		AddProject();
	}
	private: System::Void AddProjects_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		AddProjectsPath();
	}
	private: System::Void barButtonItem2_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) 
	{
		ClearProjects();
	}
	private: System::Void barButtonItem1_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) 
	{
		RemoveSelectedProject();
	}
			 
	private: System::Void StartImports_Click(System::Object^  sender, System::EventArgs^  e) //Start imports
	{
		CancelImports->Enabled = true;
		CancelImports->Visible = true;
		StartImports->Enabled = false;
		ProjectsList->Enabled = false;
		simpleButton1->Enabled = false;
		AddProjects->Enabled = false;
		bgw->RunWorkerAsync();
	}
	private: System::Void CancelImports_Click(System::Object^  sender, System::EventArgs^  e) //Cancel imports
	{
		bgw->CancelAsync();
		CancelImports->Enabled = false;
		CancelImports->Visible = false;
		StartImports->Enabled = true;
		ProjectsList->Enabled = true;
		simpleButton1->Enabled = true;
		AddProjects->Enabled = true;
	}
};
}
