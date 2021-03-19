<?php

namespace Modules\Admin\Http\Controllers;

use Illuminate\Contracts\Support\Renderable;
use Illuminate\Http\Request;
use Illuminate\Routing\Controller;
use DB;
class AboutController extends Controller
{
    public function __construct()
    {
        
        $this->middleware('auth');
    }
    /**
     * Display a listing of the resource.
     * @return Renderable
     */
    public function index()
    {
        $data['abouts'] = DB::table('abouts')
            ->where('active', 1)
            ->paginate(config('app.row'));
        return view('admin::abouts.index', $data);
        
    }

    /**
     * Show the form for creating a new resource.
     * @return Renderable
     */
    public function create()
    {
        return view('admin::abouts.create');
    }

    /**
     * Store a newly created resource in storage.
     * @param Request $request
     * @return Renderable
     */
    public function store(Request $request)
    {
        $request->validate(['title'=>'required']);
        $data = $request->except('_token', 'photo');
        if($request->photo)
        {
            $data['photo'] = $request->file('photo')->store('uploads/abouts', 'custom');
        }
        $i = DB::table('abouts')->insert($data);
        if($i)
        {
            return redirect()->route('about.create')
                ->with('success', config('app.success'));
        }
        else{
            return redirect()->route('about.create')
                ->with('error', config('app.error'))
                ->withInput();
        }
    }

   
    public function edit($id)
    {
        $about = DB::table('abouts')->find($id);
        return view('admin::abouts.edit', compact('about'));
    }

    /**
     * Update the specified resource in storage.
     * @param Request $request
     * @param int $id
     * @return Renderable
     */
    public function update(Request $request, $id)
    {
        $request->validate(['title'=>'required']);
        $about = DB::table('abouts')->find($id);
        $data = $request->except('_token', 'photo', '_method');
        if($request->photo)
        {
            $data['photo'] = $request->file('photo')->store('uploads/abouts', 'custom');
            if($about->photo)
            {
                @unlink($about->photo);
            }
        }
        $i = DB::table('abouts')->where('id', $id)->update($data);
        if($i)
        {
            return redirect()->route('about.index')
                ->with('success', config('app.success'));
        }
        else{
            return redirect()->route('about.edit', $id)
                ->with('error', config('app.error'));
                
        }
        
    }

    public function delete($id)
    {
        $i = DB::table('abouts')
            ->where('id', $id)
            ->update(['active'=>0]);
        if($i)
        {
            return redirect()->route('about.index')
                ->with('success', config('app.delete'));
        }
        else{
            return redirect()->route('about.index')
                ->with('error', config('app.fail_del'));
        }     
    }
}
