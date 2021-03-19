<?php

namespace Modules\Admin\Http\Controllers;

use Illuminate\Contracts\Support\Renderable;
use Illuminate\Http\Request;
use Illuminate\Routing\Controller;
use DB;
use Auth;
class UserController extends Controller
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
        $data['users'] = DB::table('users')
            ->paginate(config('app.row'));
        return view('admin::users.index', $data);
    }

    /**
     * Show the form for creating a new resource.
     * @return Renderable
     */
    public function create()
    {
        return view('admin::users.create');
    }

    /**
     * Store a newly created resource in storage.
     * @param Request $request
     * @return Renderable
     */
    public function store(Request $request)
    {
        $request->validate([
            'name' => 'required|min:3',
            'email' => 'required|min:5|unique:users',
            'password' => 'required|min:3'
        ]);
        $data = $request->except('_token', 'password', 'photo');
        $data['password'] = bcrypt($request->password);
        if($request->photo)
        {
            $data['photo'] = $request->file('photo')->store('uploads/users', 'custom');
        }
        $i = DB::table('users')->insert($data);
        if($i)
        {
            return redirect()->route('user.create')
                ->with('success', config('app.success'));
        }
        else{
            return redirect()->route('user.create')
                ->with('error', config('app.error'))
                ->withInput();
        }
    }

    

    /**
     * Show the form for editing the specified resource.
     * @param int $id
     * @return Renderable
     */
    public function edit($id)
    {
        $data['user'] = DB::table('users')->find($id);
        return view('admin::users.edit', $data);
    }

    /**
     * Update the specified resource in storage.
     * @param Request $request
     * @param int $id
     * @return Renderable
     */
    public function update(Request $request, $id)
    {
        $data = array(
            'name' => $request->name,
            'email' => $request->email
        );
        if($request->password)
        {
            $data['-password'] = bcrypt($request->password);
        }
        if($request->photo)
        {
            $data['photo'] = $request->file('photo')->store('uploads/users', 'custom');
        }
        $i = DB::table('users')->where('id', $id)
            ->update($data);
        if($i)
        {
            return redirect()->route('user.edit', $id)
                ->with('success', config('app.success'));
        }
        else{
            return redirect()->route('user.edit', $id)
                ->with('error', config('app.error'));
        }
    }
    public function delete($id)
    {
        $user = DB::table('users')->find($id);
        $i = DB::table('users')->where('id', $id)->delete();
        if($i)
        {
            if($user->photo)
            {
                @unlink($user->photo);
            }
            return redirect()->route('user.index')
                ->with('success', 'Data has been removed!');
        }
        else{
            return redirect()->route('user.index')
            ->with('erorr', 'Fail to delete data!');
        }
    }
    public function logout()
    {
        Auth::logout();
        return redirect('admin');
    }
    public function reset_password()
    {
        return view('admin::users.reset');
    }
    public function save_password(Request $request)
    {
        $pass = $request->password;
        $cpass = $request->cpassword;
        if($pass!=$cpass)
        {
            return redirect()->route('user.reset')
             ->with('error', 'Password and confirmed password is not matched!');
        }
        $pass = bcrypt($pass);
        $i = DB::table('users')
             ->where('id', Auth::user()->id)
             ->update(['password'=>$pass]);
        if($i)
        {
            return redirect()->route('user.reset')
            ->with('success', 'New password has been saved!');
        }
        else{
            return redirect()->route('user.reset')
            ->with('error', 'Fail to change password!');
        }
    }
}
