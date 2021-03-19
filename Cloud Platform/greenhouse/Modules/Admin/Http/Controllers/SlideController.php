<?php

namespace Modules\Admin\Http\Controllers;

use Illuminate\Contracts\Support\Renderable;
use Illuminate\Http\Request;
use Illuminate\Routing\Controller;
use DB;
use Image;
class SlideController extends Controller
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
        $slides = DB::table('slides')
            ->where('active', 1)
            ->paginate(config('app.row'));
        return view('admin::slides.index', compact('slides'));
    }

    /**
     * Show the form for creating a new resource.
     * @return Renderable
     */
    public function create()
    {
        return view('admin::slides.create');
    }

    /**
     * Store a newly created resource in storage.
     * @param Request $request
     * @return Renderable
     */
    public function store(Request $request)
    {
        $request->validate([
            'title' => 'required',
            'url' => 'required'
        ]);
        $data = $request->except('_token', 'photo');
        $file = $request->file('photo');
        $ext = $file->getClientOriginalExtension();
        $file_name = md5(date('Y-m-d-H-i-s')) . "." . $ext;
        $size = getimagesize($file);
        $path = "uploads/slides/";
        if($size[0]>1200)
        {
            $new_img =Image::make($file->getRealPath())->resize(1200, null, function($asp){
                $asp->aspectRatio();
            });
            $new_img->save($path.$file_name, 80);
        }
        else{
            $new_img =Image::make($file->getRealPath());
            $new_img->save($path.$file_name, 100);
        }
        $data['photo'] = $path . $file_name;
        $i = DB::table('slides')->insert($data);
        if($i)
        {
            return redirect()->route('slide.create')
                ->with('success', config('app.success'));
        }
        else{
            return redirect()->route('slide.create')
                ->with('error', config('app.error'))
                ->withInput();
        }
    }

    public function edit($id)
    {
        $slide = DB::table('slides')->find($id);
        return view('admin::slides.edit', compact('slide'));
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
            'title' => 'required',
            'url' => 'required'
        ]);
        $data = $request->except('_token', 'photo', '_method');
        if($request->photo)
        {
            $data['photo'] = $request->file('photo')->store('uploads/slides', 'custom');
        }
        $slide = DB::table('slides')->find($id);
        $i = DB::table('slides')->where('id', $id)->update($data);

        if($i)
        {
            if($slide->photo)
            {
                @unlink($slide->photo);
            }
            return redirect()->route('slide.edit', $id)
                ->with('success', config('app.success'));
        }
        else{
            return redirect()->route('slide.edit', $id)
                ->with('error', config('app.error'));
             
        }
    }

    public function delete($id)
    {
        $i = DB::table('slides')
            ->where('id', $id)
            ->update(['active'=>0]);
        if($i)
        {
            return redirect()->route('slide.index')
                ->with('success', config('app.delete'));
        }
        else{
            return redirect()->route('slide.index')
                ->with('error', config('app.fail_del'));
        }     
    }
}
