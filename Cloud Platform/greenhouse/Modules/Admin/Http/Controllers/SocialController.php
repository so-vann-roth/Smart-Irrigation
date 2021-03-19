<?php

namespace Modules\Admin\Http\Controllers;

use Illuminate\Contracts\Support\Renderable;
use Illuminate\Http\Request;
use Illuminate\Routing\Controller;
use DB;
class SocialController extends Controller
{
    public function __construct()
    {
        $this->middleware('auth');
    }
    
    public function index()
    {
        $data['socials'] = DB::table('socials')
            ->where('active', 1)
            ->paginate(config('app.row'));
        return view('admin::socials.index', $data);
    }

    /**
     * Show the form for creating a new resource.
     * @return Renderable
     */
    public function create()
    {
        return view('admin::socials.create');
    }

    /**
     * Store a newly created resource in storage.
     * @param Request $request
     * @return Renderable
     */
    public function store(Request $request)
    {
        $request->validate([
            'name' => 'required',
            'icon' => 'required',
            'url' => 'required'

           
        ]);
        $i = DB::table('socials')->insert($request->except('_token'));
        if($i)
        {
            return redirect()->route('social.create')
                ->with('success', config('app.success'));
        }
        else{
            return redirect()->route('social.create')
                ->with('error', config('app.error'))
                ->withInput();
        }
    }

    public function edit($id)
    {
        $data['social'] = DB::table('socials')->find($id);
        return view('admin::socials.edit', $data);
    }

    /**
     * Update the specified resource in storage.
     * @param Request $request
     * @param int $id
     * @return Renderable
     */
    public function update(Request $request, $id)
    {
        $request->validate([
            'name' => 'required',
            'icon' => 'required',
            'url' => 'required'
        ]);
        $data = $request->except(['_token', '_method']);
        $i = DB::table('socials')
            ->where('id',$id)
            ->update($data);
        if($i)
        {
            return redirect()->route('social.edit', $id)
                ->with('success', config('app.success'));
        }
        else{
            return redirect()->route('social.edit', $id)
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
        $i = DB::table('socials')
            ->where('id', $id)
            ->update(['active'=>0]);
        if($i)
        {
            return redirect()->route('social.index')
                ->with('success', config('app.delete'));
        }
        else{
            return redirect()->route('social.index')
                ->with('error', config('app.fail_del'));
        }     
    }
}
