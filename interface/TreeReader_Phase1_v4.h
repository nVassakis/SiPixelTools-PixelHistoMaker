class TreeReader {
 
 public:
  TreeReader(RunData* _run, LumiData* _lumi, EventData* _evt, 
	     EventData* _traj_evt, TrajMeasurement* _traj, 
	     EventData* _clu_evt, Cluster* _clu) { 
    run_=_run; lumi_=_lumi; evt_=_evt;
    traj_evt_=_traj_evt; traj_=_traj;
    clu_evt_=_clu_evt; clu_=_clu;
    tg_traj_evt_ = 1; tg_traj_traj_ = 1; tg_traj_mod_on_ = 1; tg_traj_clu_ = 1; tg_traj_trk_ = 1; tg_traj_mod_ = 0;
    tg_clu_evt_ = 1; tg_clu_mod_on_ = 1; tg_clu_mod_ = 0; tg_clu_clu_ = 1;
  }
  ~TreeReader() { }

 private:
  TFile f_;

  // Toggle reading branches on-off (only for trajTree)
  int tg_traj_evt_;
  int tg_traj_traj_; 
  int tg_traj_mod_on_; 
  int tg_traj_clu_; 
  int tg_traj_trk_; 
  int tg_traj_mod_;
  int tg_clu_evt_;
  int tg_clu_mod_on_; 
  int tg_clu_mod_;
  int tg_clu_clu_;
  
  // Trees
  TTree* runTree_;
  TTree* lumiTree_;
  TTree* eventTree_;
  TTree* trajTree_;
#if CLUST_LOOP > 0
  TTree* clustTree_;
#endif
  
  // Data structures
  RunData*         run_;
  LumiData*        lumi_;
  EventData*       evt_;
  EventData*       traj_evt_;
  TrajMeasurement* traj_;
  EventData*       clu_evt_;
  Cluster*         clu_;
  TrackData*       trk_;
  Digi*            digi_;
  
  // Number of entries
  long long int nrun_;
  long long int nls_;
  long long int nevt_;
  long long int nhit_;
  long long int nclu_;
  long long int ntrk_;
  long long int ndig_;

  int debug_;
#if CLUST_LOOP > 0
  void read_(TFile *f, RunData& _run, LumiData& _lumi, EventData& _evt, 
	     EventData& _traj_evt, TrajMeasurement& _traj, 
	     EventData& _clu_evt, Cluster& _clu, std::string subdir="") { 
#else
  void read_(TFile *f, RunData& _run, LumiData& _lumi, EventData& _evt, 
	     EventData& _traj_evt, TrajMeasurement& _traj, std::string subdir="") { 
#endif
    debug_=0;
    if (debug_) std::cout<<"start ok"<<std::endl;

    //  // runTree
    //  runTree_ = (TTree*)f->Get((subdir+"runTree").c_str());
    //  nrun_ = (long long int)runTree_->GetEntries();
    //  TBranch* b_r_run    = runTree_->GetBranch("run");
    //  b_r_run    ->SetAddress(&_run);

    //  // lumiTree
    //  lumiTree_ = (TTree*)f->Get((subdir+"lumiTree").c_str());
    //  nls_ = (long long int)lumiTree_->GetEntries();
    //  TBranch* b_l_lumi    = lumiTree_->GetBranch("lumi");
    //  b_l_lumi    ->SetAddress(&_lumi);

    // eventTree
    eventTree_ = (TTree*)f->Get((subdir+"eventTree").c_str());
    nevt_ = (long long int)eventTree_->GetEntries();
    TBranch* b_e_evt    = eventTree_->GetBranch("event");
    b_e_evt     ->SetAddress(&_evt);
    // trajTree
    trajTree_ = (TTree*)f->Get((subdir+"trajTree").c_str());
    nhit_ = (long long int)trajTree_->GetEntries();

    if (debug_) std::cout<<"trees1 ok"<<std::endl;

    TBranch* b_t_evt     = trajTree_->GetBranch("event");
    TBranch* b_t_mod_on  = trajTree_->GetBranch("mod_on");
    TBranch* b_t_mod     = trajTree_->GetBranch("mod");
    TBranch* b_t_clu     = trajTree_->GetBranch("clust");
    TBranch* b_t_clu_adc = trajTree_->GetBranch("clust_adc");
    TBranch* b_t_clu_pix = trajTree_->GetBranch("clust_pix");
    TBranch* b_t_trk     = trajTree_->GetBranch("track");
    TBranch* b_t_traj    = trajTree_->GetBranch("traj");
    b_t_evt     ->SetAddress(&_traj_evt);
    b_t_mod_on  ->SetAddress(&_traj.mod_on);
    b_t_mod     ->SetAddress(&_traj.mod);
    b_t_clu     ->SetAddress(&_traj.clu);
    b_t_clu_adc ->SetAddress(&_traj.clu.adc);
    b_t_clu_pix ->SetAddress(&_traj.clu.pix);
    b_t_trk     ->SetAddress(&_traj.trk);
    b_t_traj    ->SetAddress(&_traj);
    trajTree_   ->SetBranchStatus("event",     tg_traj_evt_);
    trajTree_   ->SetBranchStatus("mod_on",    tg_traj_mod_on_);
    trajTree_   ->SetBranchStatus("mod",       tg_traj_mod_);
    trajTree_   ->SetBranchStatus("clust",     tg_traj_clu_);
    trajTree_   ->SetBranchStatus("clust_adc", tg_traj_clu_);
    trajTree_   ->SetBranchStatus("clust_pix", tg_traj_clu_);
    trajTree_   ->SetBranchStatus("track",     tg_traj_trk_);
    trajTree_   ->SetBranchStatus("traj",      tg_traj_traj_);

    if (debug_) std::cout<<"trees2 ok"<<std::endl;

    // clustTree
#if CLUST_LOOP > 0
    clustTree_ = (TTree*)f->Get((subdir+"clustTree").c_str());
    nclu_  = (long long int)clustTree_->GetEntries();
    TBranch* b_c_evt     = clustTree_->GetBranch("event");
    TBranch* b_c_mod_on  = clustTree_->GetBranch("mod_on");
    TBranch* b_c_mod     = clustTree_->GetBranch("mod");
    TBranch* b_c_clu     = clustTree_->GetBranch("clust");
    TBranch* b_c_clu_adc = clustTree_->GetBranch("clust_adc");
    TBranch* b_c_clu_pix = clustTree_->GetBranch("clust_pix");
    b_c_evt     ->SetAddress(&_clu_evt);
    b_c_mod_on  ->SetAddress(&_clu.mod_on);
    b_c_mod     ->SetAddress(&_clu.mod);
    b_c_clu     ->SetAddress(&_clu);
    b_c_clu_adc ->SetAddress(&_clu.adc);
    b_c_clu_pix ->SetAddress(&_clu.pix);
    clustTree_  ->SetBranchStatus("event",     tg_clu_evt_);
    clustTree_  ->SetBranchStatus("mod_on",    tg_clu_mod_on_);
    clustTree_  ->SetBranchStatus("mod",       tg_clu_mod_);
    clustTree_  ->SetBranchStatus("clust",     tg_clu_clu_);
    clustTree_  ->SetBranchStatus("clust_adc", tg_clu_clu_);
    clustTree_  ->SetBranchStatus("clust_pix", tg_clu_clu_);
    if (debug_) std::cout<<"trees3 ok"<<std::endl;
#endif

    severity=0;
  }
  
 public:
  // Problems
  int severity;

  //Accessors
  // Entries
  long long int nrun() { return nrun_; }
  long long int nls()  { return nls_; }
  long long int nevt() { return nevt_; }
  long long int nhit() { return nhit_; }
  long long int nclu() { return nclu_; }
  // Read Entries
  void run_read(long long int i)  { runTree_->GetEntry(i); }
  void lumi_read(long long int i) { lumiTree_->GetEntry(i); }
  void evt_read(long long int i)  { eventTree_->GetEntry(i); }
  Int_t traj_read(long long int i) { Int_t read = trajTree_->GetEntry(i); return read; }
#if CLUST_LOOP > 0
  Int_t clu_read(long long int i) { return clustTree_->GetEntry(i); }
#endif
  // Memory adress of entry
  const RunData&         run()      { return *run_; }
  const LumiData&        lumi()     { return *lumi_; }
  const EventData&       evt()      { return *evt_; }
  const EventData&       traj_evt() { return *traj_evt_; }
  const TrajMeasurement& traj()     { return *traj_; }
#if CLUST_LOOP > 0
  const EventData&       clu_evt()  { return *clu_evt_; }
  const Cluster&         clu()      { return *clu_; }
#endif
  // Modifiers
#if CLUST_LOOP > 0
  void readtrees(TFile *f, std::string subdir="") { read_(f, *run_, *lumi_, *evt_, *traj_evt_, *traj_, *clu_evt_, *clu_, subdir); }
#else
  void readtrees(TFile *f, std::string subdir="") { read_(f, *run_, *lumi_, *evt_, *traj_evt_, *traj_, subdir); }
#endif
  
};
