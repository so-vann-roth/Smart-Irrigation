<?php

namespace Modules\Admin\Http\Controllers;

use Illuminate\Contracts\Support\Renderable;
use Illuminate\Http\Request;
use Illuminate\Routing\Controller;
use DB;
class TeamController extends Controller
{
    public function __construct()
    {
        $this->middleware('auth');
    }
    public function index()
    {
        $data['teams'] = DB::table('teams')
            ->where('active', 1)
            ->paginate(config('app.row'));
        return view('admin::teams.index', $data);
    }

    /**
     * Show the form for creating a new resource.
     * @return Renderable
     */
    public function create()
    {
        return view('admin::teams.create');
    }

    /**
     * Store a newly created resource in storage.
     * @param Request $request
     * @return Renderable
     */
    public function store(Request $request)
    {
        $request->validate(['name'=>'required']);
        $data = $request->except('_token', 'photo');
        if($request->photo)
        {
            $data['photo'] = $request->file('photo')->store('uploads/teams', 'custom');
        }
        $i = DB::table('teams')->insert($data);
        if($i)
        {
            return redirect()->route('team.create')
                ->with('success', config('app.success'));
        }
        else{
            return redirect()->route('team.create')
                ->with('error', config('app.error'))
                ->withInput();
        }
    }

    /**
     * Show the specified resource.
     * @param int $id
     * @return Renderable
     */
    public function show($id)
    {
        return view('admin::show');
    }

    /**
     * Show the form for editing the specified resource.
     * @param int $id
     * @return Renderable
     */
    public function edit($id)
    {
        $team = DB::table('teams')->find($id);
        return view('admin::teams.edit', compact('team'));
    }

    /**
     * Update the specified resource in storage.
     * @param Request $request
     * @param int $id
     * @return Renderable
     */
    public function update(Request $request, $id)
    {
        $request->validate(['name'=>'required']);
        $team = DB::table('teams')->find($id);
        $data = $request->except('_token', 'photo', '_method');
        if($request->photo)
        {
            $data['photo'] = $request->file('photo')->store('uploads/teams', 'custom');
            if($team->photo)
            {
                @unlink($team->photo);
            }
        }
        $i = DB::table('teams')->where('id', $id)->update($data);
        if($i)
        {
            return redirect()->route('team.index')
                ->with('success', config('app.success'));
        }
        else{
            return redirect()->route('team.edit', $id)
                ->with('error', config('app.error'));
                
        }
        
    }

    /**
     * Remove the specified resource from storage.
     * @param int $id
     * @return Renderable
     */
    public function delete($id)
    {
        $i = DB::table('teams')
            ->where('id', $id)
            ->update(['active'=>0]);
        if($i)
        {
            return redirect()->route('team.index')
                ->with('success', config('app.delete'));
        }
        else{
            return redirect()->route('team.index')
                ->with('error', config('app.fail_del'));
        }     
    }
}
